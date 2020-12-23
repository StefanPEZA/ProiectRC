/********************************************************************************
** Form generated from reading UI file 'songinfowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SONGINFOWIDGET_H
#define UI_SONGINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_songInfoWidget
{
public:
    QFrame *frame;
    QLineEdit *songPlace;
    QTextEdit *songDesc;
    QLineEdit *songTitle;
    QPushButton *songVoteUp;
    QPushButton *songVoteDown;
    QPushButton *songComments;
    QLineEdit *songVotes;
    QPushButton *songDelete;

    void setupUi(QWidget *songInfoWidget)
    {
        if (songInfoWidget->objectName().isEmpty())
            songInfoWidget->setObjectName(QString::fromUtf8("songInfoWidget"));
        songInfoWidget->resize(979, 171);
        songInfoWidget->setMinimumSize(QSize(979, 162));
        songInfoWidget->setStyleSheet(QString::fromUtf8("background-color:#263238;\n"
"color:white;"));
        frame = new QFrame(songInfoWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 979, 171));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        songPlace = new QLineEdit(frame);
        songPlace->setObjectName(QString::fromUtf8("songPlace"));
        songPlace->setGeometry(QRect(10, 10, 41, 21));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        songPlace->setFont(font);
        songPlace->setStyleSheet(QString::fromUtf8("border:none;border-radius:5px;"));
        songPlace->setReadOnly(true);
        songDesc = new QTextEdit(frame);
        songDesc->setObjectName(QString::fromUtf8("songDesc"));
        songDesc->setGeometry(QRect(10, 40, 841, 121));
        QFont font1;
        font1.setPointSize(12);
        songDesc->setFont(font1);
        songDesc->setStyleSheet(QString::fromUtf8("color:white;\n"
"\n"
"a{\n"
"	text-decoration: none;\n"
"}"));
        songDesc->setReadOnly(true);
        songTitle = new QLineEdit(frame);
        songTitle->setObjectName(QString::fromUtf8("songTitle"));
        songTitle->setGeometry(QRect(50, 10, 811, 21));
        QFont font2;
        font2.setPointSize(13);
        font2.setBold(false);
        font2.setWeight(50);
        songTitle->setFont(font2);
        songTitle->setStyleSheet(QString::fromUtf8("border:none;border-radius:5px;"));
        songTitle->setReadOnly(true);
        songVoteUp = new QPushButton(frame);
        songVoteUp->setObjectName(QString::fromUtf8("songVoteUp"));
        songVoteUp->setGeometry(QRect(860, 100, 111, 25));
        songVoteUp->setFont(font1);
        songVoteUp->setCursor(QCursor(Qt::PointingHandCursor));
        songVoteUp->setStyleSheet(QString::fromUtf8("QPushButton:disabled {\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    background-color: rgb(46, 52, 54);\n"
"}"));
        songVoteDown = new QPushButton(frame);
        songVoteDown->setObjectName(QString::fromUtf8("songVoteDown"));
        songVoteDown->setEnabled(true);
        songVoteDown->setGeometry(QRect(860, 130, 111, 25));
        songVoteDown->setFont(font1);
        songVoteDown->setCursor(QCursor(Qt::PointingHandCursor));
        songVoteDown->setStyleSheet(QString::fromUtf8("QPushButton:disabled {\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    background-color: rgb(46, 52, 54);\n"
"}"));
        songComments = new QPushButton(frame);
        songComments->setObjectName(QString::fromUtf8("songComments"));
        songComments->setGeometry(QRect(860, 70, 111, 25));
        songComments->setFont(font1);
        songComments->setCursor(QCursor(Qt::PointingHandCursor));
        songComments->setStyleSheet(QString::fromUtf8("QPushButton:disabled {\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    background-color: rgb(46, 52, 54);\n"
"}"));
        songVotes = new QLineEdit(frame);
        songVotes->setObjectName(QString::fromUtf8("songVotes"));
        songVotes->setGeometry(QRect(860, 10, 111, 21));
        songVotes->setFont(font2);
        songVotes->setStyleSheet(QString::fromUtf8("border:none;border-radius:5px;"));
        songVotes->setReadOnly(true);
        songDelete = new QPushButton(frame);
        songDelete->setObjectName(QString::fromUtf8("songDelete"));
        songDelete->setGeometry(QRect(860, 40, 111, 25));
        songDelete->setFont(font1);
        songDelete->setCursor(QCursor(Qt::PointingHandCursor));
        songDelete->setStyleSheet(QString::fromUtf8("QPushButton:disabled {\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    background-color: rgb(46, 52, 54);\n"
"}"));

        retranslateUi(songInfoWidget);

        QMetaObject::connectSlotsByName(songInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *songInfoWidget)
    {
        songInfoWidget->setWindowTitle(QCoreApplication::translate("songInfoWidget", "Form", nullptr));
        songPlace->setText(QCoreApplication::translate("songInfoWidget", "00.", nullptr));
        songTitle->setText(QCoreApplication::translate("songInfoWidget", "song_title and author", nullptr));
        songVoteUp->setText(QCoreApplication::translate("songInfoWidget", "voteaza", nullptr));
        songVoteDown->setText(QCoreApplication::translate("songInfoWidget", "retrage votul", nullptr));
        songComments->setText(QCoreApplication::translate("songInfoWidget", "comentarii", nullptr));
        songVotes->setText(QCoreApplication::translate("songInfoWidget", "voturi:", nullptr));
        songDelete->setText(QCoreApplication::translate("songInfoWidget", "sterge", nullptr));
    } // retranslateUi

};

namespace Ui {
    class songInfoWidget: public Ui_songInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SONGINFOWIDGET_H
