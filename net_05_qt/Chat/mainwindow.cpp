#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <iostream>

int connect_socket (int domain, int type, int protocol) {
    return socket( domain, type, protocol );
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect( ui->sendButton, SIGNAL(clicked()), this, SLOT(play()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::play()
{
    QString qstring ;
    QObject* button = QObject::sender();

    ui->sendButton->setEnabled( false );

    int valid = this->socket.valid ;
    if( ! valid ) {
        const char * hostNameText   = ui->hostName->displayText().toUtf8().constData();
        const char * portNoText     = "100" ;

        this->connectServer( hostNameText, portNoText );

        qDebug() << "hostName = [" << hostNameText << "]" ;
        qDebug() << "portNo   = [" << portNoText << "]";
    }

    if ( valid and button == ui->sendButton) {
        qstring = ui->message->displayText();

        if( 1 > qstring.size() ) {
            qstring = " ";
        }

        Message message ;
        message.text = qstring.toUtf8().constData() ;

        Socket * socket = & this->socket ;
        socket->writeMessage( & message );

        ui->message->setText( "" );

        qDebug() << "Message sent = " << qstring ;
    }

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
