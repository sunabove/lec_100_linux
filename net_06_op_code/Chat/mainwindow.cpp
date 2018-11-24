#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <iostream>

#include "zf_log.h"

int connect_socket (int domain, int type, int protocol) {
    return socket( domain, type, protocol );
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->sendButton->setEnabled( false );
    ui->message->setEnabled( false );

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

    const char * hostNameText   = ui->hostName->displayText().toUtf8().constData();
    const char * portNoText     = "100" ;

    ZF_LOGD( "hostName = %s", hostNameText );
    ZF_LOGD( "portNo   = %s", portNoText );

    int valid = this->connectServer( hostNameText, portNoText );

    ui->connButton->setEnabled( ! valid );

    ui->message->setEnabled( valid );
    ui->sendButton->setEnabled( valid );
}

void MainWindow::slot_sendMessage() {
    ui->sendButton->setEnabled( false );

    QString qstring = ui->message->displayText();

    if( 1 > qstring.size() ) {
        qstring = " ";
    }

    OpCodeMsg message ;
    message.textSize = qstring.toUtf8().size();
    message.text = qstring.toUtf8().constData() ;

    Socket * socket = & this->socket ;
    socket->writeOpCode( & message );

    ui->message->setText( "" );

    qDebug() << "Message sent = " << qstring ;

    ui->sendButton->setEnabled( true );
}

int MainWindow::processOpCode( OpCode * opCode ) {
    QPlainTextEdit * chatContent = ui->chatContent ;

    OpCodeMsg * opCodeMsg = (OpCodeMsg * ) opCode ;

    QString qstring = QString::fromStdString( opCodeMsg->text ) ;

    qDebug() << "Message read = " << qstring << endl ;

    if( true ) {
        chatContent->insertPlainText ( qstring );
        chatContent->insertPlainText ( "\n" );
        //chatContent->moveCursor(QTextCursor::End);
    }

    return 1;
}

//
