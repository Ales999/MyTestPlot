#include "QTime"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lastPush = 20;
    QTime midnight(0,0,0);
    qsrand( midnight.secsTo(QTime::currentTime()) );
    //setGeometry(400, 250, 542, 390);

    setupPlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupPlot()
{

    setupRealMyTimePlot( ui->customPlot );

    setWindowTitle("QCustomPlot: "+demoName);
    statusBar()->clearMessage();
    ui->customPlot->replot();

}

void MainWindow::setupRealMyTimePlot(QCustomPlot *customPlot)
{
    demoName = "My Test 2.0-beta";

    QVector<double> volData, volTime;

    QDateTime start = QDateTime::currentDateTime();
    double startTime = start.toLocalTime().toTime_t();

    // First default data
    volTime.push_front(startTime);
    volData.push_front(lastPush);

    // test add
    for (int i=1; i<20; i++) {
        lastPush += (qrand()/(double)RAND_MAX-0.5)*3;
        volData.push_front( lastPush );
        volTime.push_front(startTime+60*1+i);
    }

    volData.push_front( lastPush );
    volTime.push_front(startTime+60*2);
    for (int i=1; i<20; i++) {
        lastPush += (qrand()/(double)RAND_MAX-0.5)*3;
        volData.push_front( lastPush );
        volTime.push_front(startTime+60*2+i);
    }

    volData.push_front( lastPush );
    volTime.push_front(startTime+60*3);
    for (int i=1; i<20; i++) {
        lastPush += (qrand()/(double)RAND_MAX-0.5)*3;
        volData.push_front( lastPush );
        volTime.push_front(startTime+60*3+i);
    }

    volData.push_front( lastPush );
    volTime.push_front(startTime+60*4);
    for (int i=1; i<20; i++) {
        lastPush += (qrand()/(double)RAND_MAX-0.5)*3;
        volData.push_front( lastPush );
        volTime.push_front(startTime+60*4+i);
    }

    volData.push_front( lastPush );
    volTime.push_front(startTime+60*5);
    for (int i=1; i<20; i++) {
        lastPush += (qrand()/(double)RAND_MAX-0.5)*3;
        volData.push_front( lastPush );
        volTime.push_front(startTime+60*5+i);
    }


    double binSize = 600; //  3600*24; // bin data in 1 day intervals

    // ohls for 2.0-beta
    QCPFinancial *ohlc = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
    ohlc->setName("OHLC");
    ohlc->setChartStyle(QCPFinancial::csOhlc);
    ohlc->data()->set(QCPFinancial::timeSeriesToOhlc(volTime, volData, binSize/10.0, startTime)); // divide binSize by 3 just to make the ohlc bars a bit denser
    ohlc->setWidth(binSize*0.08); // ohlc->setWidth(binSize*0.2);
    ohlc->setTwoColored(true);

    // configure axes of both main and bottom axis rect:
    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    //dateTimeTicker->setDateTimeSpec(Qt::UTC);
    dateTimeTicker->setDateTimeFormat("hh:mm.ss");
    customPlot->xAxis->setTicker(dateTimeTicker);
    customPlot->rescaleAxes();
    customPlot->xAxis->scaleRange(1.025, customPlot->xAxis->range().center());
    customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());


    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

}
