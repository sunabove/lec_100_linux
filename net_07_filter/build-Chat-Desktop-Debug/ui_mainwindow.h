/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *hostname;
    QPushButton *connect;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *message;
    QPushButton *sendMsg;
    QPushButton *sendFile;
    QTextEdit *chatContent;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(542, 415);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        hostname = new QLineEdit(centralWidget);
        hostname->setObjectName(QStringLiteral("hostname"));

        gridLayout->addWidget(hostname, 0, 1, 1, 1);

        connect = new QPushButton(centralWidget);
        connect->setObjectName(QStringLiteral("connect"));

        gridLayout->addWidget(connect, 0, 2, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        message = new QLineEdit(centralWidget);
        message->setObjectName(QStringLiteral("message"));

        gridLayout->addWidget(message, 2, 1, 1, 1);

        sendMsg = new QPushButton(centralWidget);
        sendMsg->setObjectName(QStringLiteral("sendMsg"));

        gridLayout->addWidget(sendMsg, 2, 2, 1, 1);

        sendFile = new QPushButton(centralWidget);
        sendFile->setObjectName(QStringLiteral("sendFile"));

        gridLayout->addWidget(sendFile, 3, 2, 1, 1);

        chatContent = new QTextEdit(centralWidget);
        chatContent->setObjectName(QStringLiteral("chatContent"));

        gridLayout->addWidget(chatContent, 1, 1, 1, 2);

        horizontalSpacer = new QSpacerItem(435, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 542, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Chat Filter V1.0", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Host", Q_NULLPTR));
        hostname->setText(QApplication::translate("MainWindow", "localhost", Q_NULLPTR));
        connect->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Chat", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Message", Q_NULLPTR));
        sendMsg->setText(QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        sendFile->setText(QApplication::translate("MainWindow", "Send File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
