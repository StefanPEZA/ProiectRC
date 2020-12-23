/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *connectToServerPage;
    QPushButton *connectButton;
    QLineEdit *ipText;
    QLineEdit *portText;
    QWidget *firstPage;
    QPushButton *goToLogin;
    QPushButton *gotToRegister;
    QLabel *label;
    QWidget *loginPage;
    QPushButton *backToFirst1;
    QLineEdit *loginName;
    QLineEdit *loginPassw;
    QPushButton *loginButton;
    QWidget *registerPage;
    QPushButton *backToFirst2;
    QPushButton *registerButton;
    QLineEdit *registerName;
    QLineEdit *registerPassw;
    QLineEdit *registerLastN;
    QLineEdit *registerFirstN;
    QLineEdit *confirmRegisterPassw;
    QCheckBox *adminCheckBox;
    QLineEdit *registerAdminCode;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1040, 585);
        MainWindow->setMinimumSize(QSize(1040, 585));
        MainWindow->setMaximumSize(QSize(1040, 585));
        QFont font;
        font.setPointSize(12);
        MainWindow->setFont(font);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color:rgb(49, 49, 49);\n"
"color:white"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(20, 0, 1001, 541));
        stackedWidget->setMinimumSize(QSize(120, 80));
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color:rgb(46, 52, 54)"));
        stackedWidget->setFrameShape(QFrame::Box);
        stackedWidget->setFrameShadow(QFrame::Sunken);
        connectToServerPage = new QWidget();
        connectToServerPage->setObjectName(QString::fromUtf8("connectToServerPage"));
        connectButton = new QPushButton(connectToServerPage);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setGeometry(QRect(280, 250, 411, 61));
        connectButton->setFont(font);
        connectButton->setCursor(QCursor(Qt::PointingHandCursor));
        connectButton->setStyleSheet(QString::fromUtf8("background-color:rgb(46, 52, 54);\n"
"color:white;"));
        ipText = new QLineEdit(connectToServerPage);
        ipText->setObjectName(QString::fromUtf8("ipText"));
        ipText->setGeometry(QRect(280, 150, 411, 31));
        QFont font1;
        font1.setPointSize(14);
        ipText->setFont(font1);
        ipText->setStyleSheet(QString::fromUtf8("background-color:rgb(238, 238, 236);\n"
"color:black"));
        ipText->setInputMethodHints(Qt::ImhNone);
        ipText->setMaxLength(15);
        ipText->setFrame(true);
        ipText->setClearButtonEnabled(true);
        portText = new QLineEdit(connectToServerPage);
        portText->setObjectName(QString::fromUtf8("portText"));
        portText->setGeometry(QRect(280, 200, 411, 31));
        portText->setFont(font1);
        portText->setStyleSheet(QString::fromUtf8("background-color:rgb(238, 238, 236);\n"
"color:black"));
        portText->setMaxLength(5);
        portText->setFrame(true);
        portText->setEchoMode(QLineEdit::Normal);
        portText->setClearButtonEnabled(true);
        stackedWidget->addWidget(connectToServerPage);
        firstPage = new QWidget();
        firstPage->setObjectName(QString::fromUtf8("firstPage"));
        goToLogin = new QPushButton(firstPage);
        goToLogin->setObjectName(QString::fromUtf8("goToLogin"));
        goToLogin->setGeometry(QRect(400, 140, 151, 61));
        goToLogin->setFont(font);
        goToLogin->setCursor(QCursor(Qt::PointingHandCursor));
        goToLogin->setStyleSheet(QString::fromUtf8("background-color:rgb(46, 52, 54);\n"
"color:white;"));
        gotToRegister = new QPushButton(firstPage);
        gotToRegister->setObjectName(QString::fromUtf8("gotToRegister"));
        gotToRegister->setGeometry(QRect(400, 230, 151, 61));
        gotToRegister->setFont(font);
        gotToRegister->setCursor(QCursor(Qt::PointingHandCursor));
        gotToRegister->setStyleSheet(QString::fromUtf8("background-color:rgb(46, 52, 54);\n"
"color:white;"));
        label = new QLabel(firstPage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(350, 0, 621, 531));
        label->setStyleSheet(QString::fromUtf8("background-color:transparent"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/new/icon/icon_img")));
        label->setScaledContents(true);
        stackedWidget->addWidget(firstPage);
        label->raise();
        gotToRegister->raise();
        goToLogin->raise();
        loginPage = new QWidget();
        loginPage->setObjectName(QString::fromUtf8("loginPage"));
        backToFirst1 = new QPushButton(loginPage);
        backToFirst1->setObjectName(QString::fromUtf8("backToFirst1"));
        backToFirst1->setGeometry(QRect(280, 250, 191, 61));
        backToFirst1->setFont(font);
        backToFirst1->setCursor(QCursor(Qt::PointingHandCursor));
        backToFirst1->setStyleSheet(QString::fromUtf8("background-color:rgb(46, 52, 54);\n"
"color:white;"));
        loginName = new QLineEdit(loginPage);
        loginName->setObjectName(QString::fromUtf8("loginName"));
        loginName->setGeometry(QRect(280, 150, 411, 31));
        loginName->setFont(font1);
        loginName->setStyleSheet(QString::fromUtf8("background-color:rgb(238, 238, 236);\n"
"color:black"));
        loginName->setInputMethodHints(Qt::ImhNone);
        loginName->setMaxLength(20);
        loginName->setFrame(true);
        loginName->setClearButtonEnabled(true);
        loginPassw = new QLineEdit(loginPage);
        loginPassw->setObjectName(QString::fromUtf8("loginPassw"));
        loginPassw->setGeometry(QRect(280, 200, 411, 31));
        loginPassw->setFont(font1);
        loginPassw->setStyleSheet(QString::fromUtf8("background-color:rgb(238, 238, 236);\n"
"color:black"));
        loginPassw->setMaxLength(30);
        loginPassw->setFrame(true);
        loginPassw->setEchoMode(QLineEdit::Password);
        loginPassw->setClearButtonEnabled(true);
        loginButton = new QPushButton(loginPage);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setGeometry(QRect(500, 250, 191, 61));
        loginButton->setFont(font);
        loginButton->setCursor(QCursor(Qt::PointingHandCursor));
        loginButton->setStyleSheet(QString::fromUtf8("background-color:rgb(46, 52, 54);\n"
"color:white;"));
        stackedWidget->addWidget(loginPage);
        registerPage = new QWidget();
        registerPage->setObjectName(QString::fromUtf8("registerPage"));
        backToFirst2 = new QPushButton(registerPage);
        backToFirst2->setObjectName(QString::fromUtf8("backToFirst2"));
        backToFirst2->setGeometry(QRect(280, 360, 191, 61));
        backToFirst2->setFont(font);
        backToFirst2->setCursor(QCursor(Qt::PointingHandCursor));
        backToFirst2->setStyleSheet(QString::fromUtf8("background-color:rgb(46, 52, 54);\n"
"color:white;"));
        registerButton = new QPushButton(registerPage);
        registerButton->setObjectName(QString::fromUtf8("registerButton"));
        registerButton->setGeometry(QRect(500, 360, 191, 61));
        registerButton->setFont(font);
        registerButton->setCursor(QCursor(Qt::PointingHandCursor));
        registerButton->setStyleSheet(QString::fromUtf8("background-color:rgb(46, 52, 54);\n"
"color:white;"));
        registerName = new QLineEdit(registerPage);
        registerName->setObjectName(QString::fromUtf8("registerName"));
        registerName->setGeometry(QRect(280, 60, 411, 31));
        registerName->setFont(font1);
        registerName->setStyleSheet(QString::fromUtf8("background-color:rgb(238, 238, 236);\n"
"color:black"));
        registerName->setInputMethodHints(Qt::ImhNone);
        registerName->setMaxLength(20);
        registerName->setFrame(true);
        registerName->setClearButtonEnabled(true);
        registerPassw = new QLineEdit(registerPage);
        registerPassw->setObjectName(QString::fromUtf8("registerPassw"));
        registerPassw->setGeometry(QRect(280, 210, 411, 31));
        registerPassw->setFont(font1);
        registerPassw->setStyleSheet(QString::fromUtf8("background-color:rgb(238, 238, 236);\n"
"color:black"));
        registerPassw->setMaxLength(30);
        registerPassw->setFrame(true);
        registerPassw->setEchoMode(QLineEdit::Password);
        registerPassw->setClearButtonEnabled(true);
        registerLastN = new QLineEdit(registerPage);
        registerLastN->setObjectName(QString::fromUtf8("registerLastN"));
        registerLastN->setGeometry(QRect(280, 160, 411, 31));
        registerLastN->setFont(font1);
        registerLastN->setStyleSheet(QString::fromUtf8("background-color:rgb(238, 238, 236);\n"
"color:black"));
        registerLastN->setMaxLength(30);
        registerLastN->setFrame(true);
        registerLastN->setEchoMode(QLineEdit::Normal);
        registerLastN->setClearButtonEnabled(true);
        registerFirstN = new QLineEdit(registerPage);
        registerFirstN->setObjectName(QString::fromUtf8("registerFirstN"));
        registerFirstN->setGeometry(QRect(280, 110, 411, 31));
        registerFirstN->setFont(font1);
        registerFirstN->setStyleSheet(QString::fromUtf8("background-color:rgb(238, 238, 236);\n"
"color:black"));
        registerFirstN->setInputMethodHints(Qt::ImhNone);
        registerFirstN->setMaxLength(25);
        registerFirstN->setFrame(true);
        registerFirstN->setClearButtonEnabled(true);
        confirmRegisterPassw = new QLineEdit(registerPage);
        confirmRegisterPassw->setObjectName(QString::fromUtf8("confirmRegisterPassw"));
        confirmRegisterPassw->setGeometry(QRect(280, 260, 411, 31));
        confirmRegisterPassw->setFont(font1);
        confirmRegisterPassw->setStyleSheet(QString::fromUtf8("background-color:rgb(238, 238, 236);\n"
"color:black"));
        confirmRegisterPassw->setMaxLength(30);
        confirmRegisterPassw->setFrame(true);
        confirmRegisterPassw->setEchoMode(QLineEdit::Password);
        confirmRegisterPassw->setClearButtonEnabled(true);
        adminCheckBox = new QCheckBox(registerPage);
        adminCheckBox->setObjectName(QString::fromUtf8("adminCheckBox"));
        adminCheckBox->setGeometry(QRect(280, 310, 131, 31));
        QFont font2;
        font2.setPointSize(13);
        adminCheckBox->setFont(font2);
        adminCheckBox->setCursor(QCursor(Qt::PointingHandCursor));
        adminCheckBox->setAcceptDrops(false);
        adminCheckBox->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"color:black;\n"
"background-color:rgb(238, 238, 236);\n"
"padding-left:5px;\n"
"border:none;\n"
"border-radius: 2px;\n"
"}\n"
"\n"
"QCheckBox::indicator{\n"
"	width:20px;\n"
"	height:20px;\n"
"}\n"
"\n"
"\n"
""));
        adminCheckBox->setChecked(false);
        adminCheckBox->setAutoRepeat(false);
        adminCheckBox->setAutoExclusive(false);
        adminCheckBox->setTristate(false);
        registerAdminCode = new QLineEdit(registerPage);
        registerAdminCode->setObjectName(QString::fromUtf8("registerAdminCode"));
        registerAdminCode->setEnabled(false);
        registerAdminCode->setGeometry(QRect(410, 310, 281, 31));
        registerAdminCode->setFont(font1);
        registerAdminCode->setStyleSheet(QString::fromUtf8("background-color:rgb(238, 238, 236);\n"
"color:black"));
        registerAdminCode->setInputMethodHints(Qt::ImhNone);
        registerAdminCode->setMaxLength(5);
        registerAdminCode->setFrame(false);
        registerAdminCode->setAlignment(Qt::AlignCenter);
        registerAdminCode->setReadOnly(false);
        registerAdminCode->setClearButtonEnabled(true);
        stackedWidget->addWidget(registerPage);
        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1040, 22));
        menuBar->setStyleSheet(QString::fromUtf8("color:white;\n"
"background-color:rgb(30,30,30)"));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        menuMenu->setCursor(QCursor(Qt::ArrowCursor));
        menuMenu->setMouseTracking(true);
        menuMenu->setTearOffEnabled(false);
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionQuit);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Music Top", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "Conecteaza-te la server >>", nullptr));
        ipText->setInputMask(QString());
        ipText->setPlaceholderText(QCoreApplication::translate("MainWindow", "IP:", nullptr));
        portText->setInputMask(QString());
        portText->setPlaceholderText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        goToLogin->setText(QCoreApplication::translate("MainWindow", "Autentifica-te", nullptr));
        gotToRegister->setText(QCoreApplication::translate("MainWindow", "Inregistreaza-te", nullptr));
        label->setText(QString());
        backToFirst1->setText(QCoreApplication::translate("MainWindow", "<< Inapoi", nullptr));
        loginName->setInputMask(QString());
        loginName->setPlaceholderText(QCoreApplication::translate("MainWindow", "Numele de utilizator:", nullptr));
        loginPassw->setInputMask(QString());
        loginPassw->setPlaceholderText(QCoreApplication::translate("MainWindow", "Parola:", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "Autentificare >>", nullptr));
        backToFirst2->setText(QCoreApplication::translate("MainWindow", "<< Inapoi", nullptr));
        registerButton->setText(QCoreApplication::translate("MainWindow", "Inregistrare >>", nullptr));
        registerName->setInputMask(QString());
        registerName->setPlaceholderText(QCoreApplication::translate("MainWindow", "Numele de utilizator:", nullptr));
        registerPassw->setInputMask(QString());
        registerPassw->setPlaceholderText(QCoreApplication::translate("MainWindow", "Parola:", nullptr));
        registerLastN->setInputMask(QString());
        registerLastN->setPlaceholderText(QCoreApplication::translate("MainWindow", "Numele de familie:", nullptr));
        registerFirstN->setInputMask(QString());
        registerFirstN->setPlaceholderText(QCoreApplication::translate("MainWindow", "Prenumele", nullptr));
        confirmRegisterPassw->setInputMask(QString());
        confirmRegisterPassw->setPlaceholderText(QCoreApplication::translate("MainWindow", "Confirma parola:", nullptr));
        adminCheckBox->setText(QCoreApplication::translate("MainWindow", "Sunt admin:", nullptr));
        registerAdminCode->setInputMask(QString());
        registerAdminCode->setPlaceholderText(QCoreApplication::translate("MainWindow", "cod admin", nullptr));
        menuMenu->setTitle(QCoreApplication::translate("MainWindow", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
