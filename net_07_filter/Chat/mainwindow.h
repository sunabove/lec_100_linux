#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow , Client
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots :
    void slot_connectServer();
    void slot_sendMessage();
    void slot_sendFile();

public: int processOpCode( OpCode * opCode ) ;
public: void insertChatContent( std::string * text );
protected: void closeEvent(QCloseEvent* e) ;
};

#endif // MAINWINDOW_H
