#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <iostream>

#include "OpCodeMsg.h"

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
    ui->hostName->setReadOnly( true );

    const char * hostNameText   = ui->hostName->displayText().toUtf8().constData();
    const char * portNoText     = "100" ;

    ZF_LOGI( "hostName = %s", hostNameText );
    ZF_LOGI( "portNo   = %s", portNoText );

    ui->statusBar->showMessage( "Connecting ...." );

    int valid = this->connectServer( hostNameText, portNoText );

    ui->statusBar->showMessage( valid ? "Connected." : "Not Connected." );

    ui->connButton->setEnabled( ! valid );

    ui->hostName->setReadOnly( valid );
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

    ui->message->setText( "" );

    ZF_LOGI( "Message sent = %s", opCodeMsg.text.c_str() );

    ui->sendButton->setEnabled( true );
}

int MainWindow::processOpCode( OpCode * opCode ) {
    QPlainTextEdit * chatContent = ui->chatContent ;

    OpCodeMsg * opCodeMsg = (OpCodeMsg * ) opCode ;

    QString qstring = QString::fromStdString( opCodeMsg->text ) ;

    ZF_LOGI( "Message read = %s", opCodeMsg->text.c_str() );

    if( true ) {
        chatContent->insertPlainText ( qstring );
        chatContent->insertPlainText ( "\n" );
        //chatContent->moveCursor(QTextCursor::End);
    }

    return 1;
}

//
