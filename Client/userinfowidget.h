#ifndef USERINFOWIDGET_H
#define USERINFOWIDGET_H

#include <QWidget>
#include <QMessageBox>

namespace Ui
{
class UserInfoWidget;
}

class UserInfoWidget : public QWidget
{
        Q_OBJECT

    public:
        static int sv_sock;
        int isAdmin;
        QString username;
        int can_vote;
        int acc_type;
        int online;
        int comm_cnt;
        int vote_cnt;
        explicit UserInfoWidget(int _isAdmin, QString _name, int _type, int _can_vote, int _vote_cnt, int _comm_cnt,
                                int _online,
                                QWidget* parent = nullptr);
        ~UserInfoWidget();

    signals:
        void disconnectFromServer();

    private slots:
        void on_changeRight_clicked();

    private:
        void updateUser();
        char* SendRequestToServer(char* request);
        Ui::UserInfoWidget* ui;
};

#endif // USERINFOWIDGET_H
