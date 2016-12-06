#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "threadedobject.h"
#include "genrandom.h"
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    ThreadedObject<GenRandom>   _obj;
    int     _int_timer; // Внутренний таймер

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

signals:
    void startAction (void);		// сигнал "запуск действия"
    void doFinishSlot (void);				// сигнал "завершение работы"

public slots:
    void terminate (void); //			{ emit finish (); }		// завершение работы приложения

private slots:
    void doChangedSlot(const int &newCount);          // Появились новые данные
    void connectObjectSlot (void);		// установка связей с объектом
    void everySecSlot();
    void realtimeMyDataSlot();

protected:
    void timerEvent(QTimerEvent *ev);

private:
    Ui::MainWindow *ui;

    QString demoName;
    //QTimer dataTimer;
    QTimer alignTimer;
    QCPFinancial *ohlc;
    QVector<double> volTime, volData;

    double startTime;
    double graphStartTime;
    double timeBinSize;
    double lastPush;
    //void TestTALib();

};

#endif // MAINWINDOW_H

