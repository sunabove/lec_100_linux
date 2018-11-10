#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect slot
    connect( ui->actionExit, SIGNAL(triggered()), this, SLOT(clickButton()));

    connect( ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(clickButton()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

// click Button slot definition
void MainWindow::clickButton() {
    QObject *senderObj = sender(); // This will give Sender object
    const char * senderObjName = senderObj->objectName().toUtf8().constData();

    qDebug( "Button: %s" , senderObjName );

    if( ui->actionExit == senderObj ) {
        this->close();

        qDebug( "Exit" );
    }else if( ui->actionOpenFile == senderObj ) {
        this->openFile();

        qDebug( "OPen" );
    }
}

void MainWindow::openFile() {
    QString fileName =  QFileDialog::getOpenFileName( this,
              "Open Shape File", QDir::currentPath(), "Shape files (*.shp);;");

    if( ! fileName.isNull() ) {
        const char * filePath = fileName.toUtf8().constData() ;
        qDebug( "selected file path : %s", filePath );
    }
}
