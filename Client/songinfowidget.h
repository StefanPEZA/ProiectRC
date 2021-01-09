#ifndef SONGINFOWIDGET_H
#define SONGINFOWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QString>

namespace Ui
{
class songInfoWidget;
}

class songInfoWidget : public QWidget
{
        Q_OBJECT

    public:
        int* sv_sock;
        int acc_type;
        int place;
        int votes;
        int song_id;
        QString name;
        QString author;
        QString desc;
        QString link;
        QString genres;
        explicit songInfoWidget(int* sv_sock, int acc_type, int _place, int _song_id,
                                QString _name, QString _author, QString _desc,
                                QString _link, QString _gens, int votes, QWidget* parent = nullptr);
        char* SendRequestToServer(char* request);

        ~songInfoWidget();

    signals:
        void disconnectFromServer();
        void openCommentsPage(int song_id, const char* title);

    private slots:
        void on_songVoteUp_clicked();

        void on_songVoteDown_clicked();

        void on_songDelete_clicked();

        void on_songComments_clicked();

    private:
        Ui::songInfoWidget* ui;
};

#endif // SONGINFOWIDGET_H
