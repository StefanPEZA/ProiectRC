#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <string>

int MainWindow::sv_sock  = -1;
int MainWindow::acc_type = -1;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //https://www.youtube.com/watch?v=27PvtxWlV-o&t=260s (CrossControl)
    ui->stackedWidget->setCurrentWidget(ui->connectToServerPage);

    //expresii regulate folosite pentru a valida input-ul
    /*https://doc.qt.io/qt-5.12/qregexpvalidator.html*/
    /*https://doc.qt.io/qt-5/qlineedit.html#setValidator*/
    QRegExp     usernameRX("([a-z]|[A-Z])([a-z]|[A-Z]|\\d|_)*");
    QRegExp     lettersRX("([a-z]|[A-Z])+");
    QRegExp     numbersRX("(1|2|3|5|6|7|8|9)\\d*");
    QRegExp     ipRX("((?:\\d{1,3}.){3}\\d{1,3})|localhost");
    QValidator* validator = new QRegExpValidator(usernameRX, this);
    ui->loginName->setValidator(validator);
    ui->registerName->setValidator(validator);
    validator = new QRegExpValidator(lettersRX, this);
    ui->registerFirstN->setValidator(validator);
    ui->registerLastN->setValidator(validator);
    validator = new QRegExpValidator(numbersRX, this);
    ui->portText->setValidator(validator);
    validator = new QRegExpValidator(ipRX, this);
    ui->ipText->setValidator(validator);

    ui->portText->setText(QString::number(2121));
    ui->ipText->setText("localhost");

    topForm = new SongsTopForm(username, acc_type, &sv_sock);
    ui->stackedWidget->insertWidget(5, topForm);
    connect(topForm, SIGNAL(disconnectedFromServer()), this, SLOT(goToConnectToServer()));
    connect(topForm, SIGNAL(changeToUserPage()), this, SLOT(goToUsersPage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_connectButton_clicked()
{
    std::string textIP   = ui->ipText->text().toStdString();
    const char* IP       = textIP.c_str();
    std::string textPORT = ui->portText->text().toStdString();
    const char* PORT     = textPORT.c_str();

    if (textIP.empty() || textPORT.empty())
    {
        QMessageBox::information(this, "Camp(uri) necompletat(e)", "Va rog completati toate campurile!");
        return;
    }
    struct sockaddr_in servaddr;

    sv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sv_sock == -1)
    {
        QMessageBox::information(this, "Ceva nu e bine!", "Nu s-a putut crea socket-ul TCP!");
        return;
    }

    /*TCP_SYNCNT (since Linux 2.4)
    *         Set the number of SYN retransmits that TCP should send before
    *         aborting the attempt to connect.  It cannot exceed 255.  This
    *         option should not be used in code intended to be portable.
    * tcp(7) — Linux manual page*/
    int synRetries = 2;          // Send a total of 3 SYN packets => Timeout ~7s
    setsockopt(sv_sock, IPPROTO_TCP, TCP_SYNCNT, &synRetries, sizeof(synRetries));

    bzero(&servaddr, sizeof(servaddr));

    struct in_addr ipaddr;

    servaddr.sin_family = AF_INET;
    if (!strcmp(IP, "localhost"))
    {
        inet_aton("127.0.0.1", &ipaddr);
        servaddr.sin_addr.s_addr = ipaddr.s_addr;
    }
    else
    {
        /*Se verifica mai intai daca adresa IP data este valida*/
        if (inet_aton(IP, &ipaddr) != 0)
        {
            servaddr.sin_addr.s_addr = ipaddr.s_addr;
        }
        else
        {
            QMessageBox::information(this, "IP incorect!", "IP-ul introdus nu este valid!");
            return;
        }
    }

    int port = atoi(PORT);
    servaddr.sin_port = htons((uint16_t)port);

    //incerc sa ma conectez la server
    int connected = ::connect(sv_sock, (struct sockaddr*)&servaddr, sizeof(servaddr));

    if (connected < 0)
    {
        QMessageBox::information(this, "Ceva nu e bine!", "Conectiunea la server a esuat! (" + QString(strerror(errno)) + ")");
        return;
    }
    else
    {
        QMessageBox::information(this, "Succes", "V-ati conectat cu succes la server!");
        UserInfoWidget::sv_sock = sv_sock;
        ui->stackedWidget->setCurrentWidget(ui->firstPage);
    }
}

void MainWindow::on_loginButton_clicked()
{
    std::string textName  = ui->loginName->text().toStdString();
    const char* Name      = textName.c_str();
    std::string textPassw = ui->loginPassw->text().toStdString();
    const char* Passw     = textPassw.c_str();

    if (textName.empty() || textPassw.empty())
    {
        QMessageBox::information(this, "Camp(uri) necompletat(e)", "Va rog completati toate campurile!");
        return;
    }

    char request[512]  = ""; //se trimite la server
    char response[512] = ""; //se primeste de la server

    sprintf(request, "LOGIN|%s|%s", Name, Passw);

    if (topForm->SendRequestToServer(request, response) == 0)
    {
        ::close(sv_sock);
        ui->stackedWidget->setCurrentWidget(ui->connectToServerPage);
        return;
    }

    char* token = strtok(response, "|");

    //se verifica mai intai daca mesajul primit de la server este un esec sau un succes
    if (!strcmp(token, "FAIL"))
    {
        char* msg = strtok(NULL, "|");
        QMessageBox::information(this, "Autentificare esuata!", msg);
    }
    else if (!strcmp(token, "PASS"))
    {
        char* msg = strtok(NULL, "|");
        QMessageBox::information(this, "Autentificare reusita!", msg);
        char* type = strtok(NULL, "|");
        acc_type          = atoi(type);
        topForm->acc_type = acc_type;
        sprintf(username, "%s", Name);
        topForm->on_pushButton_clicked();
        ui->stackedWidget->setCurrentWidget(topForm); /*deschide pagina in care se or afisa topurile*/
        /*(clasa care se ocupa de managementul datelor venite de la server*/
    }
}

void MainWindow::on_registerButton_clicked()
{
    int         Account_type = 0;
    std::string textName     = ui->registerName->text().toStdString();
    const char* Name         = textName.c_str();
    std::string textPassw    = ui->registerPassw->text().toStdString();
    const char* Passw        = textPassw.c_str();
    std::string textFirstN   = ui->registerFirstN->text().toStdString();
    const char* FirstN       = textFirstN.c_str();
    std::string textLastN    = ui->registerLastN->text().toStdString();
    const char* LastN        = textLastN.c_str();

    if (textName.empty() || textPassw.empty() || textFirstN.empty() || textLastN.empty())
    {
        QMessageBox::information(this, "Camp(uri) necompletat(e)", "Va rog completati toate campurile!");
        return;
    }

    char request[512]  = ""; //se trimite la server
    char response[512] = ""; //se primeste de la server

    if (ui->registerPassw->text() != ui->confirmRegisterPassw->text())
    {
        QMessageBox::information(this, "Parola nu se potriveste",
                                 "Parola din casuta text de confirmare nu se potriveste cu parola scrisa prima data!");
        return;
    }

    //daca utilizatorul doreste sa se inregistreze ca fiind admin
    if (ui->adminCheckBox->isChecked())
    {
        /*se verifica daca codul pentru admin introdus este de 5 cifre,
         * daca este, atunci pe langa tipul de utilizator, la server mai trimitem si codul pentru a putea fi verificat*/
        if (ui->registerAdminCode->text().length() != 5)
        {
            QMessageBox::information(this, "Cod incorect", "Va rog introduceti un cod format din exact 5 cifre!");
            return;
        }
        else
        {
            Account_type = 1;
            int adminCode = ui->registerAdminCode->text().toInt();
            sprintf(request, "REGISTER|%s|%s|%s|%s|%d|%d", Name, FirstN, LastN, Passw, Account_type, adminCode);
        }
    }
    else
    {
        Account_type = 0;
        sprintf(request, "REGISTER|%s|%s|%s|%s|%d", Name, FirstN, LastN, Passw, Account_type);
    }

    if (topForm->SendRequestToServer(request, response) == 0)
    {
        ::close(sv_sock);
        ui->stackedWidget->setCurrentWidget(ui->connectToServerPage);
        return;
    }

    char* token = strtok(response, "|");

    //se verifica mai intai daca mesajul primit de la server este un esec sau un succes
    if (!strcmp(token, "FAIL"))
    {
        char* msg = strtok(NULL, "|");
        QMessageBox::information(this, "Inregistrare esuata!", msg);
    }
    else if (!strcmp(token, "PASS"))
    {
        char* msg = strtok(NULL, "|");
        acc_type = Account_type;
        QMessageBox::information(this, "Inregistrare reusita!", msg);
        topForm->acc_type = acc_type;
        sprintf(username, "%s", Name);
        topForm->on_pushButton_clicked();
        ui->stackedWidget->setCurrentWidget(topForm); /*deschide pagina in care se or afisa topurile*/
        /*(clasa care se ocupa de managementul datelor venite de la server)*/
    }
}

void MainWindow::on_backToFirst1_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->firstPage);
}

void MainWindow::on_backToFirst2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->firstPage);
}

void MainWindow::on_goToLogin_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage);
}

void MainWindow::on_gotToRegister_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->registerPage);
}

void MainWindow::on_adminCheckBox_stateChanged(int arg1)
{
    if (arg1 == Qt::CheckState::Checked)
    {
        ui->registerAdminCode->setEnabled(true);
    }
    else if (arg1 == Qt::CheckState::Unchecked)
    {
        ui->registerAdminCode->setEnabled(false);
    }
}

void MainWindow::goToConnectToServer()
{
    ui->stackedWidget->setCurrentWidget(ui->connectToServerPage);
}

void MainWindow::goToUsersPage()
{
    on_refreshUsers_clicked();
    ui->stackedWidget->setCurrentWidget(ui->showUsers);
}

void MainWindow::on_backToTop_clicked()
{
    topForm->on_pushButton_clicked();
    ui->stackedWidget->setCurrentWidget(topForm);
}

void MainWindow::on_refreshUsers_clicked()
{
    char request[2048]    = "";               //se trimite la server
    char response[102400] = "";               //se primeste de la server

    strcpy(request, "GET_USERS|");

    //trimiterea cererii(request) si primirea raspunsului(response)
    if (topForm->SendRequestToServer(request, response) == 0)
    {
        ui->stackedWidget->setCurrentWidget(ui->connectToServerPage);
        ::close(sv_sock);
        return;
    }

    ui->usersList->clear();
    char* nr_users = strtok(response, "|");

    if (!strcmp(nr_users, "FAIL"))
    {
        char* text = strtok(NULL, "|");
        ui->usersList->addItem(text);
    }
    else
    {
        for (int i = 1; i <= atoi(nr_users); i++)
        {
            char* name    = strtok(NULL, "|");
            int type  = atoi(strtok(NULL, "|"));
            int can_vote    = atoi(strtok(NULL, "|"));
            int vote_cnt    = atoi(strtok(NULL, "|"));
            int comm_cnt    = atoi(strtok(NULL, "|"));
            int   is_online   = atoi(strtok(NULL, "||"));

            UserInfoWidget* user;
            //se creaza un nou obiect care va contine toate informatiile despre o melodie
            user = new UserInfoWidget(acc_type, name, type, can_vote, vote_cnt, comm_cnt, is_online);
            connect(user, SIGNAL(disconnectFromServer()), this, SLOT(goToConnectToServer()));
            QListWidgetItem* item = new QListWidgetItem(ui->usersList);
            item->setSizeHint(user->minimumSize());
            //se adauga acest obiect intr-o lista care este afisata pe ecran
            ui->usersList->addItem(item);
            ui->usersList->setItemWidget(item, user);
        }
    }
}
