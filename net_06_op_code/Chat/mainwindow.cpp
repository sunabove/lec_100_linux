#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <iostream>

#include "OpCodeMsg.h"
#include "OpCodeSysInfo.h"
#include "OpCodeExit.h"

int connect_socket (int domain, int type, int protocol) {
    return socket( domain, type, protocol );
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->sendButton->setEnabled( false );
    ui->message->setEnabled( false );

    ui->statusBar->showMessage( "HANSEI Chat v.1.0" );

    connect( ui->connButton , SIGNAL(clicked()), this, SLOT(slot_connectServer()));
    connect( ui->sendButton , SIGNAL(clicked()), this, SLOT(slot_sendMessage()));
    connect( ui->message    , SIGNAL(returnPressed()), this, SLOT(slot_sendMessage()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::slot_connectServer() {
    ui->connButton->setEnabled( false );
    ui->sendButton->setEnabled( false );
    ui->hostName->setEnabled( false );
    ui->chatContent->setEnabled( false );

    const char * hostNameText   = ui->hostName->displayText().toUtf8().constData();
    const char * portNoText     = "100" ;

    ZF_LOGI( "hostName = %s", hostNameText );
    ZF_LOGI( "portNo   = %s", portNoText );

    ui->statusBar->showMessage( "Connecting ...." );

    int valid = this->connectServer( hostNameText, portNoText );

    ui->statusBar->showMessage( valid ? "Connected." : "Not Connected." );

    ui->connButton->setEnabled( ! valid );

    ui->hostName->setEnabled( ! valid );
    ui->chatContent->setEnabled( valid );
    ui->sendButton->setEnabled( valid );
    ui->message->setEnabled( valid );

}

void MainWindow::slot_sendMessage() {
    ui->sendButton->setEnabled( false );

    QString qstring = ui->message->displayText();

    if( 1 > qstring.size() ) {
        qstring = " ";
    }

    OpCodeMsg opCodeMsg ;
    opCodeMsg.text = 1 > qstring.size() ? " " : qstring.toUtf8().constData() ;

    Socket * socket = & this->socket ;
    socket->writeOpCode( & opCodeMsg );

    //ui->message->setText( "" );

    ZF_LOGI( "Message sent = %s", opCodeMsg.text.c_str() );

    ui->sendButton->setEnabled( true );
}

int MainWindow::processOpCode( OpCode * opCode ) {

    auto code = opCode->code ;

    if( OP_CODE_MSG == code ) {
        OpCodeMsg * opCodeMsg = (OpCodeMsg * ) opCode ;
        this->insertChatContent( & opCodeMsg->text );
    } else if( OP_CODE_SYS_INFO == code ) {
        OpCodeSysInfo * opCodeSysInfo = (OpCodeSysInfo * ) opCode ;
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
        opCodeExit.exitCode = 0 ;
        socket->writeOpCode( & opCodeExit );

        ZF_LOGI( "Done. sending exit message." );
        // -- send exit message
    }

    this->close();
}
// -- closeEvent

//
