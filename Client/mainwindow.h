#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "songstopform.h"
#include "userinfowidget.h"
#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
        Q_OBJECT
    public:
        static int sv_sock;
        static int acc_type;
        char username[25] = "none";
        MainWindow(QWidget* parent = nullptr);

        ~MainWindow();

    private slots:
        void on_actionQuit_triggered();
        void on_actionDeconecteaza_te_triggered();
        void on_gotToRegister_clicked();
        void on_goToLogin_clicked();
        void on_backToFirst1_clicked();
        void on_backToFirst2_clicked();
        void on_connectButton_clicked();
        void on_loginButton_clicked();
        void on_registerButton_clicked();
        void on_adminCheckBox_stateChanged(int arg1);
        void goToConnectToServer();
        void goToUsersPage();
        void on_refreshUsers_clicked();
        void on_backToTop_clicked();

    private:
        SongsTopForm* topForm;

        Ui::MainWindow* ui;
};
#endif // MAINWINDOW_H
