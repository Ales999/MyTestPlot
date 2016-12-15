#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QTimer>

#include "threadedobject.h"
#include "genrandom.h"
#include "qcustomplot.h"
#include "itestplotview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public ITestPlotView
{
    Q_OBJECT
    //Q_INTERFACES(ITestPlotView)

    ThreadedObject<GenRandom>   _obj;
    int     _int_timer; // Внутренний таймер

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setStatusBarMassage(QString message) const;
    void setAskTable(DepthModel *askModel) const;
    void setBidTable(DepthModel *bidModel) const;

    // for test
    void setAskTable(QAbstractItemModel *model) const;

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
    void startFinish (void);				// сигнал "завершение работы"

public slots:

private slots:
    void everySecSlot();
    void realtimeMyDataSlot();

protected:


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

