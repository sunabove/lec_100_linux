#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect slot
    connect( ui->myPushButton, SIGNAL(clicked()), this, SLOT(clickButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// click Button slot definition
void MainWindow::clickButton() {
    ui->myLabel->setText( ui->myLineEdit->text() );
}
