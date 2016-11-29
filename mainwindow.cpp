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
    setGeometry(400, 250, 1042, 390);
    //
    setupPlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

///
/// \brief MainWindow::my_rand
/// \param accuracy - количество десятичных знаков
///
double MainWindow::my_rand(int accuracy)
{
    double ret = 0;
    ret = ( qrand() % int (qPow(10, accuracy) +1) ) / qPow(10, accuracy);
    return ret;
}

double MainWindow::my_rand()
{
    return (double)( qrand()/(double)RAND_MAX-0.5 )*3;
}

void MainWindow::setupPlot()
{
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
    QVector<double> loTime, loData;
    // calculate two new data points:
    double key = sqtime.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    double lstRange=0.0;
    static double lastPointKey = 0;
    // int j = ui->customPlot->plottableCount();
    // qDebug() << j;

    //static double lastPointKey = 0;
    //double currentTime = curtime.toTime_t();;
    QDateTime currentTime = QDateTime::currentDateTime();
    //double currentData = my_rand();

    //qDebug() << ui->customPlot->plottable()->name() ;
    //QCPFinancial *ohlc = ui->customPlot->plottable()->children();

    //if (key-lastPointKey > 0.02)
    //{
         qDebug() << "Start: " << volData.count();

        InitRandomData(loTime, loData, QDateTime::currentDateTime().toTime_t(), 1);

        lstRange = loTime.last();

        this->volTime.append(loTime);
        this->volData.append(loData);



        //qDebug() << loTime.count();

        QCPFinancialDataMap dataNew = QCPFinancial::timeSeriesToOhlc(loTime, loData, this->timeBinSize, this->startTime);
        ohlc->addData(dataNew);//  ->addData(&dataNew);

        for ( int l=0; l<60; l++) {
            volData.removeFirst();
            volTime.removeFirst();
            this->graphStartTime += 1;
            this->startTime += 1;
        }

        //volTime.push_back(currentTime.toTime_t());
        // add random data to volData
        //lastPush += my_rand();
        //volData.push_back( lastPush );
        //qDebug() << "Last Data: " << lastPush;

        lastPointKey = key;
    //}
    // make key axis range scroll with the data (at a constant range size of 8):
    //ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
    //startTime +=1;

    //QCPFinancialDataMap data2 = QCPFinancial::timeSeriesToOhlc(volTime, volData, timeBinSize, startTime);
    ui->customPlot->xAxis->setRange(graphStartTime, currentTime.toTime_t()+60);
    qDebug() << "Current Start Time: " << QDateTime::fromTime_t(this->startTime).toString("d M yyyy hh:mm:ss.");
    qDebug() << "End: " << volData.count();

    ui->customPlot->replot();

    ui->customPlot->rescaleAxes();


/*
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
*/

}

void MainWindow::InitRandomData(QVector<double> &ivolTime, QVector<double> &ivolData, double startTime, uint genMinuts)
{
    for (uint n=1; n <= genMinuts; n++  )
    {
        for(int msec = 0; msec < 60; msec++ )
        {
            // add time to volTime
            ivolTime.push_back( startTime );
            // add random data to volData
            lastPush += my_rand();
            ivolData.push_back( lastPush );
            startTime += 1; // Add One second
        }
    }
}

void MainWindow::setupRealMyTimePlot(QCustomPlot *customPlot)
{
    demoName = "Моя проба";
    int genTimeMinutes = 120; // 120 минут !
    QDateTime startProgTime = QDateTime::currentDateTime();

    QDateTime toBackTime = startProgTime.addSecs(0-(genTimeMinutes*60));
    //qDebug() << "Back, 120 min, Time: " << toBackTime.toString("d M yyyy hh:mm:ss.z");

    //toBackTime.setTimeSpec(Qt::UTC);

    this->graphStartTime = toBackTime.toTime_t();

    // Заполним первоначальными данными на два часа (7200 элементов в каждом векторе будет)
    InitRandomData(volTime, volData, graphStartTime, genTimeMinutes);
    this->startTime = startProgTime.toTime_t();

    //qDebug() << "Start Time: " << toBackTime.toString("d M yyyy hh:mm:ss.") << "Stop Time: " << QDateTime::fromTime_t( volTime.last() ).toString("d M yyyy hh:mm:ss.");
   qDebug() << "Start Time: " << startProgTime.toString("d M yyyy hh:mm:ss.");

    double binSize = 600; // 600 --> 10 Min, 3600*24; --> bin data in 1 day intervals
    this->timeBinSize = binSize/10; /// 5- > В каждой 10-ти минутке по 5 баров

    // ohlc for stable version
    ohlc = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(ohlc);
    QCPFinancialDataMap data2 = QCPFinancial::timeSeriesToOhlc(volTime, volData, timeBinSize, startTime); // divide binSize by 3 just to make the ohlc bars a bit denser
    ohlc->setName("OHLC");
    ohlc->setChartStyle(QCPFinancial::csOhlc);
    ohlc->setData(&data2, true);
    ohlc->setWidth(binSize*0.08);
    ohlc->setTwoColored(true);

    // bring bottom and main axis rect closer together:
    customPlot->plotLayout()->setRowSpacing(0);


    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    //customPlot->xAxis->setDateTimeFormat("hh:mm:ss\nzzz");
    customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    customPlot->xAxis->setTickLabelRotation(15);
    //customPlot->xAxis->setAutoTickCount(3); // If setAutoTickStep == true !;
    //customPlot->xAxis->  volumePos->setWidth(3600*4);

    customPlot->xAxis->setAutoTickStep(false);
    //Через сколько рисовать тикет со временем на шкале X
    customPlot->xAxis->setTickStep(600); // 600 -> 10 минут
    customPlot->xAxis->setRange(startTime, volTime.last()+60);
    customPlot->xAxis->scaleRange(1.025, customPlot->xAxis->range().center());
    customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());

    customPlot->rescaleAxes();
    // make axis rects' left side line up:
    //QCPMarginGroup *group = new QCPMarginGroup(customPlot);
    //customPlot->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, group);

    // print debug
    //qDebug() << qFloor((volTime.first()-startTime)/timeBinSize+0.5);
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeMyDataSlot()));
    //dataTimer.start(1000); // Interval 0 means to refresh as fast as possible
    dataTimer.start(60000); // interval -> 1 min



}


