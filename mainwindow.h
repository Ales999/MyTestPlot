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
    double my_rand();
    double my_rand(int accuracy);
    // Generate random time/data values
    void InitRandomData(QVector<double> &volTime, QVector<double> &volData, double startTime);
    void InitRandomData(QVector<double> &volTime, QVector<double> &volData, double startTime, uint minuteGen);
    // Setting and start QTimer's
    void setupPlot();
    void setupRealMyTimePlot(QCustomPlot *customPlot);

private slots:
  void everySecSlot();
  void realtimeMyDataSlot();

private:
    Ui::MainWindow *ui;

    QString demoName;
    QTimer dataTimer;
    QTimer timeAlign;
    QCPFinancial *ohlc;
    QVector<double> volTime, volData;

    double startTime;
    double graphStartTime;
    double timeBinSize;
    double lastPush;
    //void TestTALib();

    // My Dev version
    QCPFinancialDataMap timeSeriesToOhlcOne(const QVector<double> &time, const QVector<double> &value, double timeBinSize, double timeBinOffset);
};

#endif // MAINWINDOW_H
