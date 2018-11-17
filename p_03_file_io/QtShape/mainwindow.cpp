#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

#include "zf_log.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // connect slot
    connect( ui->actionExit,     SIGNAL(triggered()), this, SLOT(clickButton()));
    connect( ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(clickButton()));

    qApp->installEventFilter(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

bool MainWindow::eventFilter(QObject *target, QEvent *event) {
    auto objName = target->objectName().toUtf8().constData(); ;
    auto eventType = event->type() ;

    ZF_LOGI( "target obj name : %s" , objName );
    ZF_LOGI( "event type      : %d" , eventType );

    return QMainWindow::eventFilter(target, event);
}

// click Button slot definition
void MainWindow::clickButton() {
    QObject *senderObj = sender(); // This will give Sender object
    const char * senderObjName = senderObj->objectName().toUtf8().constData();

    ZF_LOGI( "Button: %s" , senderObjName );

    if( ui->actionExit == senderObj ) {
        this->close();
    }else if( ui->actionOpenFile == senderObj ) {
        this->openFile();
    }
}

void MainWindow::openFile() {
    QString fileName =  QFileDialog::getOpenFileName( this,
              "Open Shape File", QDir::currentPath(), "Shape files (*.shp);;");

    if( ! fileName.isNull() ) {
        const char * filePath = fileName.toUtf8().constData() ;
        ZF_LOGI( "selected file path : %s", filePath );
    }
}
