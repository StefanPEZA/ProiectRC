#include "userinfowidget.h"
#include "ui_userinfowidget.h"
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
#include <netinet/in.h>
#include <string>

int UserInfoWidget::sv_sock = -1;

UserInfoWidget::UserInfoWidget(int _isAdmin, QString _name, int _type, int _can_vote, int _vote_cnt, int _comm_cnt,
                               int _online,
                               QWidget* parent) :
    QWidget(parent),
    ui(new Ui::UserInfoWidget)
{
    isAdmin = _isAdmin;
    username = _name;
    acc_type = _type;
    can_vote = _can_vote;
    vote_cnt = _vote_cnt;
    comm_cnt = _comm_cnt;
    online = _online;

    ui->setupUi(this);
    updateUser();
}

UserInfoWidget::~UserInfoWidget()
{
    delete ui;
}

void UserInfoWidget::updateUser()
{
    if (isAdmin == 1)
    {
        ui->changeRight->setVisible(true);
    }
    else
    {
        ui->changeRight->setVisible(false);
    }

    ui->userName->setText(username);
    if (acc_type == 1)
    {
        ui->userName->setStyleSheet("border:none;border-radius:5px;color:lightblue;");
    }
    else
    {
        ui->userName->setStyleSheet("border:none;border-radius:5px;color:white;");
    }

    if (online == 0)
    {
        ui->onlineStatus->setText("offline");
        ui->onlineStatus->setStyleSheet("border:none;border-radius:5px;color:red;");
    }
    else
    {
        ui->onlineStatus->setText("online");
        ui->onlineStatus->setStyleSheet("border:none;border-radius:5px;color:green;");
    }

    ui->votesCount->setText("Voturi: " + QString::number(vote_cnt));
    ui->commsCount->setText("Comentarii: " + QString::number(comm_cnt));

    if (can_vote == 1)
    {
        ui->voteRight->setText("Drept de vot: Da");
        ui->changeRight->setText("Blocheaza dreptul de vot");
    }
    else
    {
        ui->voteRight->setText("Drept de vot: Nu");
        ui->changeRight->setText("Deblocheaza dreptul de vot");
    }

}

char* UserInfoWidget::SendRequestToServer(char* request)
{
    char* response = NULL;
    int len = strlen(request);

    if (write(sv_sock, &len, 4) <= 0)
    {
        QMessageBox::information(this, "Ceva nu e bine!",
                                 "Conectiunea la server a fost pierduta! (" + QString(strerror(errno)) + ")");
        return NULL;
    }
    if (write(sv_sock, request, len) <= 0)
    {
        QMessageBox::information(this, "Ceva nu e bine!",
                                 "Conectiunea la server a fost pierduta! (" + QString(strerror(errno)) + ")");
        return NULL;
    }

    if (read(sv_sock, &len, 4) <= 0)
    {
        QMessageBox::information(this, "Ceva nu e bine!",
                                 "Conectiunea la server a fost pierduta! (" + QString(strerror(errno)) + ")");
        return NULL;
    }
    response = new char[len + 1];
    int bytesRead = 0;
    int result;
    while (bytesRead < len)
    {
        result = read(sv_sock, response + bytesRead, len - bytesRead);
        if (result < 1 )
        {
            delete[] response;
            QMessageBox::information(this, "Ceva nu e bine!",
                                     "Conectiunea la server a fost pierduta! (" + QString(strerror(errno)) + ")");
            return NULL;
        }

        bytesRead += result;
    }
    response[len] = '\0';
    return response;
}

void UserInfoWidget::on_changeRight_clicked()
{
    if (QMessageBox::question(this, "Schimbi dreptul de vot?",
                              "Sigur vrei sa schimbi dreptul de vot al utilizatorului: " + username + "?",
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
    {
        return;
    }
    char request[500]   = "";                  //se trimite la server
    char* response = NULL;                 //se primeste de la server

    sprintf(request, "CHANGE_RIGHT|%s|%d", username.toStdString().c_str(), !can_vote);

    //trimiterea cererii(request) si primirea raspunsului(response)
    if ((response = SendRequestToServer(request)) == NULL)
    {
        emit disconnectFromServer();
        ::close(sv_sock);
        return;
    }

    char* token = strtok(response, "|");

    if (!strcmp(token, "FAIL"))
    {
        char* text = strtok(NULL, "|");
        QMessageBox::information(this, "Ceva nu e bine!", text);
    }
    else
    {
        can_vote = can_vote ? 0 : 1;
        updateUser();
        char* text = strtok(NULL, "|");
        QMessageBox::information(this, "Succes!", text);
    }
    delete[] response;
}
