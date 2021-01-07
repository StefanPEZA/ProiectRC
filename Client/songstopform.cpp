#include "songstopform.h"
#include "ui_songstopform.h"
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

SongsTopForm::SongsTopForm(char* _username, int _acc_type, int* _sv_sock, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::SongsTopForm)
{
    ui->setupUi(this);
    username = _username;
    sv_sock  = _sv_sock;
    acc_type = _acc_type;
    ui->stackedWidget->setCurrentWidget(ui->topPage);
}

SongsTopForm::~SongsTopForm()
{
    delete ui;
}

char* SongsTopForm::SendRequestToServer(char* request)
{
    char* response = NULL;
    int len = strlen(request);

    if (write(*sv_sock, &len, 4) <= 0)
    {
        QMessageBox::information(this, "Ceva nu e bine!",
                                 "Conectiunea la server a fost pierduta! (" + QString(strerror(errno)) + ")");
        return NULL;
    }
    if (write(*sv_sock, request, len) <= 0)
    {
        QMessageBox::information(this, "Ceva nu e bine!",
                                 "Conectiunea la server a fost pierduta! (" + QString(strerror(errno)) + ")");
        return NULL;
    }

    if (read(*sv_sock, &len, 4) <= 0)
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
        result = read(*sv_sock, response + bytesRead, len - bytesRead);
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

//functia care va cere topul cu melodii de la server si il va afisa
void SongsTopForm::on_pushButton_clicked()
{
    char request[2048]    = "";               //se trimite la server
    char* response = NULL;             //se primeste de la server

    std::string req(ui->comboBox->currentText().toStdString());

    if (req == "toate")
    {
        req = "GET_TOP|";
    }
    else
    {
        req = "GET_TOP|" + req;
    }

    strncpy(request, req.c_str(), req.size());

    //trimiterea cererii(request) si primirea raspunsului(response)
    if ((response = SendRequestToServer(request)) == NULL)
    {
        emit disconnectedFromServer();
        ::close(*sv_sock);
        return;
    }

    char* nr_items = strtok(response, "|");

    ui->songList->clear();

    if (!strcmp(nr_items, "FAIL"))
    {
        char* text = strtok(NULL, "|");
        ui->songList->addItem(text);
    }
    else
    {
        for (int i = 1; i <= atoi(nr_items); i++)
        {
            int   song_id = atoi(strtok(NULL, "|"));
            char* name    = strtok(NULL, "|");
            char* author  = strtok(NULL, "|");
            char* desc    = strtok(NULL, "|");
            char* link    = strtok(NULL, "|");
            char* gens    = strtok(NULL, "|");
            int   votes   = atoi(strtok(NULL, "||"));

            songInfoWidget* info;
            //se creaza un nou obiect care va contine toate informatiile despre o melodie
            info = new songInfoWidget(sv_sock, acc_type, i, song_id, name, author, desc, link, gens, votes);
            connect(info, SIGNAL(disconnectFromServer()), this, SLOT(emitDisconnectSignal()));
            connect(info, SIGNAL(openCommentsPage(int, const char*)), this, SLOT(goToComments(int, const char*)));
            QListWidgetItem* item = new QListWidgetItem(ui->songList);
            item->setSizeHint(info->minimumSize());
            //se adauga acest obiect intr-o lista care este afisata pe ecran
            ui->songList->addItem(item);
            ui->songList->setItemWidget(item, info);
        }
    }
    delete[] response;
}

void SongsTopForm::emitDisconnectSignal()
{
    emit disconnectedFromServer();
}

void SongsTopForm::goToComments(int _song_id, const char* _title)
{
    char request[2048]    = "";                //se trimite la server
    char* response = NULL;                //se primeste de la server

    sprintf(request, "GET_COMMS|%d", _song_id);

    //trimiterea cererii(request) si primirea raspunsului(response)
    if ((response = SendRequestToServer(request)) == NULL)
    {
        emit disconnectedFromServer();
        ::close(*sv_sock);
        return;
    }

    char* nr_items = strtok(response, "|");
    int   count    = atoi(nr_items);

    ui->commentsList->clear();

    if (!strcmp(nr_items, "FAIL"))
    {
        char* text = strtok(NULL, "|");
        ui->commentsList->addItem(text);
    }
    else
    {
        for (int i = 1; i <= count; i++)
        {
            char* name    = strtok(NULL, "|");
            char* comment = strtok(NULL, "||");

            ui->commentsList->addItem("[>> Scris de \"" + QString(name) + "\" <<]:\n" + QString(comment));
        }
    }
    delete[] response;
    song_id = _song_id;
    ui->songTitle->setText(_title);
    ui->stackedWidget->setCurrentWidget(ui->commentPage);
}

void SongsTopForm::on_postComment_clicked()
{
    char request[2048]   = "";                  //se trimite la server
    char* response = NULL;                 //se primeste de la server

    std::string com     = ui->commentText->toPlainText().toStdString();
    const char* comment = com.c_str();

    sprintf(request, "ADD_COMM|%d|%s", song_id, comment);

    //trimiterea cererii(request) si primirea raspunsului(response)
    if ((response = SendRequestToServer(request)) == NULL)
    {
        emit disconnectedFromServer();
        ::close(*sv_sock);
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
        ui->commentText->setPlainText("");
        std::string title = ui->songTitle->text().toStdString();
        goToComments(song_id, title.c_str());
    }
    delete[] response;
}

void SongsTopForm::on_goBackButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->topPage);
}

void SongsTopForm::on_goToUsers_clicked()
{
    emit changeToUserPage();
}

void SongsTopForm::on_goToAddSong_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->addSongPage);
}

void SongsTopForm::on_goBack2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->topPage);
}

void SongsTopForm::on_addSongButton_clicked()
{
    char request[2048]   = "";                  //se trimite la server
    char* response = NULL;                  //se primeste de la server

    std::string songname        = ui->songNameText->text().toStdString();
    std::string author      = ui->songAuthorText->text().toStdString();
    std::string description = ui->songDescText->toPlainText().toStdString();
    std::string link        = ui->songLinkText->text().toStdString();
    std::string genres      = ui->songGenreText->text().toStdString();

    if (songname.empty() || author.empty() || description.empty() || link.empty() || genres.empty())
    {
        QMessageBox::information(this, "Camp(uri) necompletat(e)", "Va rog completati toate campurile!");
        return;
    }

    sprintf(request, "ADD_SONG|%s|%s|%s|%s|%s", songname.c_str(), author.c_str(), description.c_str(), link.c_str(),
            genres.c_str());

    //trimiterea cererii(request) si primirea raspunsului(response)
    if ((response = SendRequestToServer(request)) == NULL)
    {
        emit disconnectedFromServer();
        ::close(*sv_sock);
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
        char* text = strtok(NULL, "|");
        ui->songNameText->setText("");
        ui->songAuthorText->setText("");
        ui->songDescText->setPlainText("");
        ui->songLinkText->setText("");
        ui->songGenreText->setText("");
        QMessageBox::information(this, "Succes!", text);
    }
    delete[] response;
}
