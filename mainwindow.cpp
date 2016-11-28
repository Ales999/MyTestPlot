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
    setGeometry(400, 250, 542, 390);
    //value2 = new QVector<double>(500);
    setupPlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupPlot()
{
    //setupFinPlot(ui->customPlot);
    //setupRealTimePlot(ui->customPlot);
    setupRealMyTimePlot( ui->customPlot );

    setWindowTitle("QCustomPlot: "+demoName);
    statusBar()->clearMessage();
    ui->customPlot->replot();

}

void MainWindow::realtimeDataSlot()
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
      // add data to lines:
      ui->customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
      ui->customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
      // rescale value (vertical) axis to fit the current data:
      //ui->customPlot->graph(0)->rescaleValueAxis();
      //ui->customPlot->graph(1)->rescaleValueAxis(true);
      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->customPlot->replot();

    /*
    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
            , 0);
      lastFpsKey = key;
      frameCount = 0;
    }
*/

}

void MainWindow::realtimeMyDataSlot()
{

    static QTime sqtime(QTime::currentTime());
    // calculate two new data points:
    double key = sqtime.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    //double testrnd;
    //double mytmp;

    //static double lastPointKey = 0;
    //double currentTime = curtime.toTime_t();;
    QDateTime currentTime = QDateTime::currentDateTime();
    double currentData = 20;

    //qsrand(9);
    if (key-lastPointKey > 0.02) // at most add point every 20 ms
    {
        //  Удалить последний
        if( !this->volData.isEmpty() )
        {
            currentData = this->volData.last();
            if (volData.size() > 500)
                {
                   this->volTime.removeFirst();
                   this->volData.removeFirst();
                }
        }

        // Добавить данные в конец вектора
        this->volTime.push_front(currentTime.toTime_t());

        lastPush += (qrand()/(double)RAND_MAX-0.5)*3;
        this->volData.push_back( lastPush );

      lastPointKey = key;
    }


    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->customPlot->replot();


    if(!this->volData.isEmpty())
    {
        //
        ui->statusBar->showMessage(
          QString("Value2: %1")
                .arg(this->volData.last())
                ,0);

    }
    else
    {
        ui->statusBar->showMessage(QString("valu2 is empty"));
    }

    ui->customPlot->rescaleAxes();

}

void MainWindow::setupRealMyTimePlot(QCustomPlot *customPlot)
{
    demoName = "Моя проба";

    QVector<double> volData, volTime;
    const double timeShift = 60;

    //QDateTime tstart = QDateTime::currentDateTime(); //  QDateTime(QDate(2016, 11, 27));
    QDateTime tstart = QDateTime::QDateTime(QDate(2016, 11, 27));
    tstart.setTimeSpec(Qt::UTC);
    //double startTime = tstart.toLocalTime().toTime_t();
    double startTime = tstart.toTime_t();

    //volTime.setSharable(true);
    //volData.setSharable(true);

    // Первый заброс данных во время и данные
    volTime.push_front(startTime);
    volData.push_front(lastPush);

    // test add
    for (int i=1; i<20; i++) {
        lastPush += (qrand()/(double)RAND_MAX-0.5)*3;
        volData.push_front( lastPush );
        volTime.push_front(startTime+timeShift*1+i*2);
    }

    volData.push_front( lastPush );
    volTime.push_front(startTime+timeShift*2);
    for (int i=1; i<20; i++) {
        lastPush += (qrand()/(double)RAND_MAX-0.5)*3;
        volData.push_front( lastPush );
        volTime.push_front(startTime+timeShift*2+i*2);
    }

    volData.push_front( lastPush );
    volTime.push_front(startTime+timeShift*3);
    for (int i=1; i<20; i++) {
        lastPush += (qrand()/(double)RAND_MAX-0.5)*3;
        volData.push_front( lastPush );
        volTime.push_front(startTime+timeShift*3+i*2);
    }

    volData.push_front( lastPush );
    volTime.push_front(startTime+timeShift*4);
    for (int i=1; i<20; i++) {
        lastPush += (qrand()/(double)RAND_MAX-0.5)*3;
        volData.push_front( lastPush );
        volTime.push_front(startTime+timeShift*4+i*2);
    }

    volData.push_front( lastPush );
    volTime.push_front(startTime+timeShift*5);
    for (int i=1; i<20; i++) {
        lastPush += (qrand()/(double)RAND_MAX-0.5)*3;
        volData.push_front( lastPush );
        volTime.push_front(startTime+timeShift*5+i*2);
    }


    double binSize = 60; //  3600*24; // bin data in 1 day intervals
    double timeBinSize = binSize/5.0;

    // ohlc for stable version
    QCPFinancial *ohlc = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(ohlc);
    QCPFinancialDataMap data2 = QCPFinancial::timeSeriesToOhlc(volTime, volData, timeBinSize, startTime); // divide binSize by 3 just to make the ohlc bars a bit denser
    ohlc->setName("OHLC");
    ohlc->setChartStyle(QCPFinancial::csOhlc);
    ohlc->setData(&data2, true);
    ohlc->setWidth(binSize*0.08);
    ohlc->setTwoColored(true);


    customPlot->xAxis->setAutoTickStep(false);
    //customPlot->xAxis->setTickStep(3600*24*4); // 4 day tickstep
    customPlot->xAxis->setTickStep(120); // 4 day tickstep
    //volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("dd:hh:mm\nss:zzz");
    customPlot->rescaleAxes();
    customPlot->xAxis->scaleRange(1.025, customPlot->xAxis->range().center());
    customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());


    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // print debug
    qDebug() << qFloor((volTime.first()-startTime)/timeBinSize+0.5);


}


