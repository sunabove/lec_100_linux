#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Shape.h"

using namespace esri ;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ShapeFile shapeFile ;

public :
    bool eventFilter(QObject *target, QEvent *event) ;
    void openFile();

public slots:
    void clickButton();
};

#endif // MAINWINDOW_H
