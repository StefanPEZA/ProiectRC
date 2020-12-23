/********************************************************************************
** Form generated from reading UI file 'songstopform.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SONGSTOPFORM_H
#define UI_SONGSTOPFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SongsTopForm
{
public:
    QStackedWidget *stackedWidget;
    QWidget *topPage;
    QPushButton *pushButton;
    QComboBox *comboBox;
    QListWidget *songList;
    QLineEdit *songGenre;
    QWidget *commentPage;
    QListWidget *commentsList;
    QPushButton *postComment;
    QPlainTextEdit *commentText;
    QPushButton *goBackButton;
    QLineEdit *songTitle;

    void setupUi(QWidget *SongsTopForm)
    {
        if (SongsTopForm->objectName().isEmpty())
            SongsTopForm->setObjectName(QString::fromUtf8("SongsTopForm"));
        SongsTopForm->resize(1001, 541);
        SongsTopForm->setMinimumSize(QSize(1001, 541));
        SongsTopForm->setMaximumSize(QSize(1001, 541));
        SongsTopForm->setStyleSheet(QString::fromUtf8("background-color:rgb(46, 52, 54);\n"
"color:white;"));
        stackedWidget = new QStackedWidget(SongsTopForm);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 1001, 541));
        stackedWidget->setMinimumSize(QSize(1001, 541));
        stackedWidget->setMaximumSize(QSize(1001, 541));
        stackedWidget->setStyleSheet(QString::fromUtf8("color:white"));
        topPage = new QWidget();
        topPage->setObjectName(QString::fromUtf8("topPage"));
        pushButton = new QPushButton(topPage);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(160, 10, 131, 31));
        QFont font;
        font.setPointSize(12);
        pushButton->setFont(font);
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton->setFocusPolicy(Qt::StrongFocus);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	color:white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    background-color: rgb(85, 87, 83);\n"
"}"));
        comboBox = new QComboBox(topPage);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(50, 10, 111, 31));
        comboBox->setFont(font);
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox{ \n"
"color:white;\n"
"background-color: rgb(46, 52, 54); \n"
"}"));
        songList = new QListWidget(topPage);
        songList->setObjectName(QString::fromUtf8("songList"));
        songList->setGeometry(QRect(0, 50, 1001, 481));
        songList->setFont(font);
        songList->setStyleSheet(QString::fromUtf8(""));
        songList->setFrameShape(QFrame::Box);
        songList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        songList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        songList->setSelectionMode(QAbstractItemView::NoSelection);
        songList->setIconSize(QSize(0, 0));
        songList->setMovement(QListView::Static);
        songList->setSpacing(2);
        songList->setViewMode(QListView::ListMode);
        songList->setItemAlignment(Qt::AlignHCenter);
        songGenre = new QLineEdit(topPage);
        songGenre->setObjectName(QString::fromUtf8("songGenre"));
        songGenre->setGeometry(QRect(10, 10, 41, 31));
        QFont font1;
        font1.setPointSize(13);
        font1.setBold(false);
        font1.setWeight(50);
        songGenre->setFont(font1);
        songGenre->setStyleSheet(QString::fromUtf8("border:none;border-radius:5px;color:white;"));
        songGenre->setFrame(false);
        stackedWidget->addWidget(topPage);
        commentPage = new QWidget();
        commentPage->setObjectName(QString::fromUtf8("commentPage"));
        commentsList = new QListWidget(commentPage);
        commentsList->setObjectName(QString::fromUtf8("commentsList"));
        commentsList->setGeometry(QRect(0, 60, 1001, 401));
        commentsList->setFont(font);
        commentsList->setFrameShape(QFrame::Box);
        commentsList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        commentsList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        commentsList->setSelectionMode(QAbstractItemView::NoSelection);
        commentsList->setSpacing(5);
        commentsList->setWordWrap(true);
        postComment = new QPushButton(commentPage);
        postComment->setObjectName(QString::fromUtf8("postComment"));
        postComment->setGeometry(QRect(860, 480, 131, 51));
        postComment->setFont(font);
        postComment->setCursor(QCursor(Qt::PointingHandCursor));
        postComment->setFocusPolicy(Qt::StrongFocus);
        postComment->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	color:white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    background-color: rgb(85, 87, 83);\n"
"}"));
        commentText = new QPlainTextEdit(commentPage);
        commentText->setObjectName(QString::fromUtf8("commentText"));
        commentText->setGeometry(QRect(0, 479, 851, 51));
        commentText->setFont(font);
        commentText->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        commentText->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        goBackButton = new QPushButton(commentPage);
        goBackButton->setObjectName(QString::fromUtf8("goBackButton"));
        goBackButton->setGeometry(QRect(10, 10, 121, 31));
        goBackButton->setFont(font);
        goBackButton->setCursor(QCursor(Qt::PointingHandCursor));
        goBackButton->setFocusPolicy(Qt::StrongFocus);
        goBackButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	color:white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    background-color: rgb(85, 87, 83);\n"
"}"));
        songTitle = new QLineEdit(commentPage);
        songTitle->setObjectName(QString::fromUtf8("songTitle"));
        songTitle->setGeometry(QRect(140, 10, 821, 31));
        songTitle->setFont(font1);
        songTitle->setStyleSheet(QString::fromUtf8("border:none;border-radius:5px;"));
        songTitle->setReadOnly(true);
        stackedWidget->addWidget(commentPage);
        QWidget::setTabOrder(pushButton, songList);
        QWidget::setTabOrder(songList, songGenre);
        QWidget::setTabOrder(songGenre, comboBox);

        retranslateUi(SongsTopForm);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SongsTopForm);
    } // setupUi

    void retranslateUi(QWidget *SongsTopForm)
    {
        SongsTopForm->setWindowTitle(QCoreApplication::translate("SongsTopForm", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("SongsTopForm", "Reimprospatare", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("SongsTopForm", "nimic", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("SongsTopForm", "Electronic", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("SongsTopForm", "Hip-hop", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("SongsTopForm", "House", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("SongsTopForm", "Pop", nullptr));

        songGenre->setText(QCoreApplication::translate("SongsTopForm", "Gen", nullptr));
        postComment->setText(QCoreApplication::translate("SongsTopForm", "Posteaza", nullptr));
        goBackButton->setText(QCoreApplication::translate("SongsTopForm", "<< Inapoi", nullptr));
        songTitle->setText(QCoreApplication::translate("SongsTopForm", "song_title and author", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SongsTopForm: public Ui_SongsTopForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SONGSTOPFORM_H
