#ifndef SONGSTOPFORM_H
#define SONGSTOPFORM_H

#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QListWidget>

#include "songinfowidget.h"

namespace Ui
{
class SongsTopForm;
}

class SongsTopForm : public QWidget
{
        Q_OBJECT

    public:
        char* username;
        int acc_type;
        explicit SongsTopForm(char* username, int _acc_type, int* _sv_sock, QWidget* parent = nullptr);
        char* SendRequestToServer(char* request);
        ~SongsTopForm();

    private:
        int song_id;
        int* sv_sock;
        Ui::SongsTopForm* ui;

    signals:
        void disconnectedFromServer();
        void changeToUserPage();

    public slots:
        void on_pushButton_clicked();
        void emitDisconnectSignal();
        void goToComments(int song_id, const char* title);
        void on_postComment_clicked();
        void on_goBackButton_clicked();
    private slots:
        void on_goToUsers_clicked();
        void on_goToAddSong_clicked();
        void on_goBack2_clicked();
        void on_addSongButton_clicked();
};

#endif // SONGSTOPFORM_H
