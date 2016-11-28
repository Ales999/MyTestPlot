#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupPlot();
    void setupRealMyTimePlot(QCustomPlot *customPlot);

private:
    Ui::MainWindow *ui;
    QString demoName;
    QTimer dataTimer;
    double lastPush;

};

#endif // MAINWINDOW_H
