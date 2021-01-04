#include "songinfowidget.h"
#include "ui_songinfowidget.h"
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

songInfoWidget::songInfoWidget(int* _sv_sock, int _acc_type, int _place, int _song_id, QString _name, QString _author,
                               QString _desc,
                               QString _link, QString _gens, int _votes, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::songInfoWidget)
{
    ui->setupUi(this);

    sv_sock  = _sv_sock;
    acc_type = _acc_type;
    place    = _place;
    song_id  = _song_id;
    name     = _name;
    author   = _author;
    desc     = _desc;
    link     = _link;
    genres   = _gens;
    votes    = _votes;

    ui->songDesc->setHtml("Genuri muzicale: " + genres + "</div><br><br><div style=\"white-space: pre-wrap;\">" + desc);
    ui->songTitle->setText(name + QString(" - ") + author);
    ui->songPlace->setText(QString::number(place) + ".");
    ui->songVotes->setText(QString("Voturi: ") + QString::number(votes));
    if (acc_type == 0)
    {
        ui->songDelete->setEnabled(false);
        ui->songDelete->setVisible(false);
    }
    ui->label->setText("<a style = \"text-decoration:none;color:#F2AA4C\" href = \"" + link + "\">" + link + "</a>");
}

int songInfoWidget::SendRequestToServer(char* request, char* response)
{
    int len = strlen(request);

    if (write(*sv_sock, &len, 4) <= 0)
    {
        QMessageBox::information(this, "Ceva nu e bine!",
                                 "Conectiunea la server a fost pierduta! (" + QString(strerror(errno)) + ")");
        return (0);
    }
    if (write(*sv_sock, request, len) <= 0)
    {
        QMessageBox::information(this, "Ceva nu e bine!",
                                 "Conectiunea la server a fost pierduta! (" + QString(strerror(errno)) + ")");
        return (0);
    }

    if (read(*sv_sock, &len, 4) <= 0)
    {
        QMessageBox::information(this, "Ceva nu e bine!",
                                 "Conectiunea la server a fost pierduta! (" + QString(strerror(errno)) + ")");
        return (0);
    }
    if (read(*sv_sock, response, len) <= 0)
    {
        QMessageBox::information(this, "Ceva nu e bine!",
                                 "Conectiunea la server a fost pierduta! (" + QString(strerror(errno)) + ")");
        return (0);
    }
    response[len] = '\0';
    return (1);
}

songInfoWidget::~songInfoWidget()
{
    delete ui;
}

void songInfoWidget::on_songVoteUp_clicked()
{
    char request[2048]   = "";               //se trimite la server
    char response[10240] = "";               //se primeste de la server

    sprintf(request, "VOTE_UP|%d", song_id);

    //trimiterea cererii(request) si primirea raspunsului(response)
    if (SendRequestToServer(request, response) == 0)
    {
        ::close(*sv_sock);
        emit disconnectFromServer();
        return;
    }

    char* token = strtok(response, "|");
    if (!strcmp(token, "FAIL"))
    {
        char* msg = strtok(NULL, "|");
        QMessageBox::information(this, "Ceva nu a mers bine", QString(msg));
    }
    else
    {
        QMessageBox::information(this, "Multumim!", "Ai votat cu succes melodia: " + name + " - " + author);
    }
}

void songInfoWidget::on_songVoteDown_clicked()
{
    char request[2048]   = "";                //se trimite la server
    char response[10240] = "";                //se primeste de la server

    sprintf(request, "VOTE_DOWN|%d", song_id);

    //trimiterea cererii(request) si primirea raspunsului(response)
    if (SendRequestToServer(request, response) == 0)
    {
        ::close(*sv_sock);
        emit disconnectFromServer();
        return;
    }

    char* token = strtok(response, "|");
    if (!strcmp(token, "FAIL"))
    {
        char* msg = strtok(NULL, "|");
        QMessageBox::information(this, "Ceva nu a mers bine!", QString(msg));
    }
    else
    {
        QMessageBox::information(this, "Nu-ti mai place?",
                                 "Ti-ai retras votul cu succes de la melodia: " + name + " - " + author);
    }
}

void songInfoWidget::on_songDelete_clicked()
{
    if (QMessageBox::question(this, "Esti sigur?", "Sigur vrei sa stergi melodia din top?",
                              QMessageBox::Yes | QMessageBox::No)
            != QMessageBox::Yes)
    {
        return;
    }
    char request[2048]   = "";                 //se trimite la server
    char response[10240] = "";                 //se primeste de la server

    sprintf(request, "DELETE_SONG|%d", song_id);

    //trimiterea cererii(request) si primirea raspunsului(response)
    if (SendRequestToServer(request, response) == 0)
    {
        ::close(*sv_sock);
        emit disconnectFromServer();
        return;
    }

    char* token = strtok(response, "|");
    if (!strcmp(token, "FAIL"))
    {
        char* msg = strtok(NULL, "|");
        QMessageBox::information(this, "Ceva nu a mers bine!", QString(msg));
    }
    else
    {
        QMessageBox::information(this, "Succes, din pacate!",
                                 "Stergerea melodiei a avut loc cu succes! \n" + name + " - " + author);
    }
}

void songInfoWidget::on_songComments_clicked()
{
    ui->songTitle->setText(name + QString(" - ") + author);
    std::string title = name.toStdString() + std::string(" - ") + author.toStdString();

    emit openCommentsPage(song_id, title.c_str());
}
