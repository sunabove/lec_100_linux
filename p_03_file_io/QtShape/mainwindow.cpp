#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTemporaryFile>

#include "zf_log.h"

using namespace esri ;

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
    bool debug = false ;
    auto objName = target->objectName().toUtf8().constData(); ;
    auto eventType = event->type() ;

    if( debug ) { 
        ZF_LOGI( "target obj name : %s" , objName );
        ZF_LOGI( "event type      : %d" , eventType );
    }

    return QMainWindow::eventFilter(target, event);
}

// click Button slot definition
void MainWindow::clickButton() {
    bool debug = true ;
    QObject *senderObj = sender(); // This will give Sender object
    const char * senderObjName = senderObj->objectName().toUtf8().constData();

    if( debug ) { ZF_LOGI( "Button: %s" , senderObjName ); }

    if( ui->actionExit == senderObj ) {
        this->close();
    } else if( ui->actionOpenFile == senderObj ) {
        this->openFile();
    }
}

void MainWindow::openFile() {
    auto qtPath = QDir::homePath();
    qtPath = QDir::currentPath();

    QString qFileName = QFileDialog::getOpenFileName( this, "Open Shape File",
                       qtPath, "Shape files (*.shp);;" );

    if( qFileName.isNull() ) {
        ZF_LOGI( "qFileName.isNull()" );
    } else if( ! qFileName.isNull() ) {
        string error ;

        errno = 0 ;

        auto filePath = qFileName.toUtf8().constData();
        ZF_LOGI( "File path = %s" , filePath );

        FILE * file = fopen( filePath, "rb" );

        auto shapeFile = & this->shapeFile ;

        error = readShapeFile( shapeFile , file );

        if( 0 < error.size() ) {
            QMessageBox messageBox;
            messageBox.critical( 0, "Error", error.c_str() );
            messageBox.setFixedSize(500,200);
        }

    }
}
