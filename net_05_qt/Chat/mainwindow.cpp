#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // slot
    //QPushButton* sendButton = this->findChild<QPushButton*>("sendButton");

    connect( ui->sendButton, SIGNAL(clicked()), this, SLOT(play()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::play()
{
    QString piece;
    QObject* button = QObject::sender();

    if (button == ui->sendButton)
    {
        piece = ui->message->text();
    }

    // std::cout << "Starting to play:" << piece.toUtf8().constData();

    qDebug() << "Starting to play:" << piece;
}

// --
