#ifndef SONGSTOPFORM_H
#define SONGSTOPFORM_H

#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QListWidget>

#include "songinfowidget.h"

namespace Ui {
class SongsTopForm;
}

class SongsTopForm : public QWidget
{
   Q_OBJECT

public:
   char *username;
   int acc_type;
   explicit SongsTopForm(char *username, int _acc_type, int *_sv_sock, QWidget *parent = nullptr);
   ~SongsTopForm();

private:
   int song_id;
   int *sv_sock;
   Ui::SongsTopForm *ui;
   int SendRequestToServer(char *request, char *response);

signals:
   void disconnectedFromServer();

public slots:
   void on_pushButton_clicked();
   void emitDisconnectSignal();
   void goToComments(int song_id, const char *title);
   void on_postComment_clicked();
   void on_goBackButton_clicked();
};

#endif // SONGSTOPFORM_H
