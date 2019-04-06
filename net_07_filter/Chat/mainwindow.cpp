#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

#include <QFileDialog>
#include <QMessageBox>
#include <QTemporaryFile>

#include <iostream>

#include "OpCodeMsg.h"
#include "OpCodeSysInfo.h"
#include "OpCodeExit.h"

int connect_socket (int domain, int type, int protocol) {
    return socket( domain, type, protocol );
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->sendMsg->setEnabled( false );
    ui->message->setEnabled( false );
    ui->sendFile->setEnabled( false );

    ui->statusBar->showMessage( "HANSEI Chat v.1.0" );

    connect( ui->connect    , SIGNAL(clicked())         , this, SLOT(slot_connectServer()));
    connect( ui->sendMsg    , SIGNAL(clicked())         , this, SLOT(slot_sendMessage()));
    connect( ui->message    , SIGNAL(returnPressed())   , this, SLOT(slot_sendMessage()));
    connect( ui->sendFile   , SIGNAL(clicked())        , this, SLOT(slot_sendFile()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::slot_connectServer() {
    ui->connect->setEnabled( false );
    ui->sendMsg->setEnabled( false );
    ui->sendFile->setEnabled( false );
    ui->hostname->setEnabled( false );
    ui->chatContent->setEnabled( false );

    const char * hostNameText   = ui->hostname->displayText().toUtf8().constData();
    const char * portNoText     = "100" ;

    ZF_LOGI( "hostName = %s", hostNameText );
    ZF_LOGI( "portNo   = %s", portNoText );

    ui->statusBar->showMessage( "Connecting ...." );

    int valid = this->connectServer( hostNameText, portNoText );

    ui->statusBar->showMessage( valid ? "Connected." : "Not Connected." );

    ui->connect->setEnabled( ! valid );

    ui->hostname->setEnabled( ! valid );
    ui->chatContent->setEnabled( valid );
    ui->sendMsg->setEnabled( valid );
    ui->sendFile->setEnabled( valid );
    ui->message->setEnabled( valid );
}

void MainWindow::slot_sendMessage() {
    ui->sendMsg->setEnabled( false );

    QString qstring = ui->message->displayText();

    if( 1 > qstring.size() ) {
        qstring = " ";
    }

    Socket * socket = & this->socket ;

    OpCodeMsg opCodeMsg ;
    opCodeMsg.clientId = this->clientId ;
    opCodeMsg.text = 1 > qstring.size() ? " " : qstring.toUtf8().constData() ;

    socket->writeOpCode( & opCodeMsg );

    //ui->message->setText( "" );

    ZF_LOGI( "Message sent = %s", opCodeMsg.text.c_str() );

    ui->sendMsg->setEnabled( true );
}

void MainWindow::slot_sendFile() {
    auto qtPath = QDir::homePath();
    qtPath = QDir::currentPath();

    QString qFileName = QFileDialog::getOpenFileName( this, "Open File",
                       qtPath, "Files (*);;" );

    if( qFileName.isNull() ) {
        ZF_LOGI( "qFileName.isNull()" );
    } else if( ! qFileName.isNull() ) {
        std::string error ;

        errno = 0 ;

        auto filePath = qFileName.toUtf8().constData();
        ZF_LOGI( "File path = %s" , filePath );

        FILE * file = NULL;
        file = fopen( filePath, "rb" );

        if( NULL != file ) {
            fclose( file );
        }

        if( 0 < error.size() ) {
            QMessageBox messageBox;
            messageBox.critical( 0, "Error", error.c_str() );
            messageBox.setFixedSize(500,200);
        }

    }
}

int MainWindow::processOpCode( OpCode * opCode ) {

    auto code = opCode->code ;

    if( OP_CODE_MSG == code ) {
        OpCodeMsg * opCodeMsg = (OpCodeMsg * ) opCode ;
        this->insertChatContent( & opCodeMsg->text );
    } else if( OP_CODE_SYS_INFO == code ) {
        OpCodeSysInfo * opCodeSysInfo = (OpCodeSysInfo * ) opCode ;
        this->clientId = opCodeSysInfo->clientId ;
        this->insertChatContent( & opCodeSysInfo->sysMessage );
    }

    return 1;
}

void MainWindow::insertChatContent( std::string * text ) {
    auto chatContent = ui->chatContent ;

    ZF_LOGI( "Message chat = %s", text->c_str() );

    chatContent->insertPlainText( QString::fromStdString( * text ) );
    chatContent->insertPlainText( "\n" );
    chatContent->moveCursor(QTextCursor::End);
}

// closeEvent
void MainWindow::closeEvent(QCloseEvent * ) {
    ZF_LOGI( "closeEvent" );

    Socket * socket = & this->socket ;

    if( NULL != socket and socket->valid ) {
        // send exit message
        ZF_LOGI( "Sending exit message ..." );

        OpCodeExit opCodeExit ;
        opCodeExit.clientId = clientId ;
        opCodeExit.exitCode = 0 ;
        socket->writeOpCode( & opCodeExit );

        ZF_LOGI( "Done. sending exit message." );
        // -- send exit message
    }

    this->close();
}
// -- closeEvent

//
