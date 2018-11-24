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

public: int processOpCode( OpCode * opCode ) ;
};

#endif // MAINWINDOW_H
