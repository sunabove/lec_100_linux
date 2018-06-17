#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <iostream>

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

    int valid = this->connectServer( hostNameText, portNoText );

    ui->connButton->setEnabled( ! valid );

    ui->message->setEnabled( valid );
    ui->sendButton->setEnabled( valid );

    qDebug() << "hostName = [" << hostNameText << "]" ;
    qDebug() << "portNo   = [" << portNoText << "]";
}

void MainWindow::slot_sendMessage() {
    ui->sendButton->setEnabled( false );

    QString qstring = ui->message->displayText();

    if( 1 > qstring.size() ) {
        qstring = " ";
    }

    Message message ;
    message.text = qstring.toUtf8().constData() ;

    Socket * socket = & this->socket ;
    socket->writeMessage( & message );

    ui->message->setText( "" );

    qDebug() << "Message sent = " << qstring ;

    ui->sendButton->setEnabled( true );
}

int MainWindow::processMessage( Message * message ) {
    QPlainTextEdit * chatContent = ui->chatContent ;

    QString qstring = QString::fromStdString( message->text ) ;

    qDebug() << "Message read = " << qstring << endl ;

    if( true ) {
        chatContent->insertPlainText ( qstring );
        chatContent->insertPlainText ( "\n" );
        //chatContent->moveCursor(QTextCursor::End);
    }

    return 1;
}

// --
