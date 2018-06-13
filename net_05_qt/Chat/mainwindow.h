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
    void play();

public: int processMessage( Message * message ) ;
};

#endif // MAINWINDOW_H
