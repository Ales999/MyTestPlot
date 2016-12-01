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

double MainWindow::my_rand()
{
    return (double)( qrand()/(double)RAND_MAX-0.5 )*3;
}

void MainWindow::setupPlot()
{
    //ui->gridLayout->setEnabled(false);
    ui->customPlot->setVisible(false);
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

void MainWindow::everySecSlot()
{
    static bool First = true;
    int genTimeMinutes = 3;
    QTime sqtime(QTime::currentTime());

    if( sqtime.second() == 0 )
    {
        if (First )
        {
            First = false;
            ui->customPlot->setVisible(true);
            ui->waitingLabel->setVisible(false);
            QDateTime setupTime = QDateTime(QDate::currentDate(), sqtime );
            setupTime.setTimeSpec(Qt::UTC);
            QDateTime startProgBackTime = setupTime.addSecs( 0-(genTimeMinutes*60) );
            qDebug() << "First" << setupTime.toString("hh:mm:ss");
            this->startTime         = setupTime.toTime_t();
            this->graphStartTime    = startProgBackTime.toTime_t();


            InitRandomData(volTime, volData, graphStartTime, genTimeMinutes );

            QCPFinancialDataMap data2 = QCPFinancial::timeSeriesToOhlc(volTime, volData, timeBinSize, 60);

            ohlc->setData(&data2, true);
            ui->customPlot->rescaleAxes();
            ui->customPlot->replot();
        } else
            QTimer::singleShot(0, this, SLOT(realtimeMyDataSlot()));
    }

}

void MainWindow::realtimeMyDataSlot()
{

    QVector<double> loTime, loData;
    qDebug() << "currentTime" << QTime::currentTime().toString("hh:mm:ss");

    this->startTime += 60;
    qDebug() << "this->startTime: " << QDateTime::fromTime_t(this->startTime).toString("hh:mm:ss.");

    InitRandomData(loTime, loData, this->startTime );

    qDebug() << "loTime Count: " << loTime.count();
    qDebug() << "loTime First: " << QDateTime::fromTime_t( loTime.first() ).toString("hh:mm:ss.");
    qDebug() << "loTime Last:  " << QDateTime::fromTime_t( loTime.last()  ).toString("hh:mm:ss.");
    //qDebug() << "loData Last:  " << loData.last();

    QCPFinancialDataMap dataNew = QCPFinancial::timeSeriesToOhlc(loTime, loData, this->timeBinSize, 0);

    //int currentBinIndex = qFloor((loTime.first())/this->timeBinSize+0.5); qDebug() << "Index: " << currentBinIndex;

    QMap<double,QCPFinancialData>::iterator it = dataNew.begin();
    for(;it != dataNew.end(); ++it)
        qDebug() << QDateTime::fromTime_t( it.key()  ).toString("hh:mm:ss.");

    ohlc->addData( dataNew );

    // make key axis range scroll with the data (at a constant range size of 8):
    //ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
    //ui->customPlot->xAxis->setRange(volTime.last()-60, volTime.count()-60 ,Qt::AlignRight);

    this->volTime.append(loTime);
    this->volData.append(loData);

    for ( int l=0; l<60; l++)
    {
        volTime.removeFirst();
        volData.removeFirst();
        this->graphStartTime += 1;
    }

    ui->customPlot->xAxis->setRange( volTime.first(), volTime.last() );

    qDebug() << "Update Time:   " << QDateTime::fromTime_t(this->startTime).toString("hh:mm:ss.");
    qDebug() << "Time Count:    " << volTime.count() << "Data Count: "  << volData.count();
    qDebug() << "volTime First: " << QDateTime::fromTime_t( volTime.first() ).toString("hh:mm:ss.");
    qDebug() << "volTime Last:  " << QDateTime::fromTime_t( volTime.last()  ).toString("hh:mm:ss.");

    ui->customPlot->replot();
    ui->customPlot->rescaleAxes();
    qDebug() << "--------------------------------------------------";
}

void MainWindow::InitRandomData(QVector<double> &ivolTime, QVector<double> &ivolData, double lostartTime)
{
    for(int msec = 0; msec < 60; msec++ )
    {
        ivolTime.push_back( lostartTime ); // add time to volTime
        lastPush += my_rand(); // add random data to volData
        ivolData.push_back( lastPush );

        lostartTime += 1; // Add One second
    }

}

void MainWindow::InitRandomData(QVector<double> &ivolTime, QVector<double> &ivolData, double lostartTime, uint genMinuts)
{
    bool myFirstMin = true;
    uint mingen = 0;
    do
    {
        for(int msec = 1; msec <= 59; msec++ )
        {


            if ( !volTime.isEmpty() && !volData.isEmpty() && myFirstMin )
            {
                ivolTime.push_back( lostartTime );
                ivolData.push_back( lastPush );
                myFirstMin = false;
            } else
            {
                ivolTime.push_back( lostartTime ); // add time to volTime
                lastPush += my_rand(); // add random data to volData
                ivolData.push_back( lastPush );
            }
            lostartTime += 1; // Add One second
        }
        myFirstMin = true;
        mingen++;
        lostartTime += 1;
    } while(mingen < genMinuts);
}



void MainWindow::setupRealMyTimePlot(QCustomPlot *customPlot)
{
    demoName = "Моя проба";
    int genTimeMinutes = 3; // 120 минут !
    double binSize = 60; // 600 --> 10 Min, 3600*24; --> bin data in 1 day intervals
    this->timeBinSize = binSize; //10 /// 5- > В каждой 10-ти минутке по 5 баров

    // Set startProgTime without msecs
    QTime currTime = QTime::currentTime();
    QDateTime startProgTime = QDateTime(QDate::currentDate(), QTime( currTime.hour(), currTime.minute(), currTime.second(), 0 ) );
    startProgTime.setTimeSpec(Qt::UTC);

    QDateTime startProgBackTime = startProgTime.addSecs( 0-(genTimeMinutes*60) );

    this->startTime         = startProgTime.toTime_t();
    this->graphStartTime    = startProgBackTime.toTime_t();

    qDebug() << "Start Program Time: " << startProgTime.toString("d M yyyy hh:mm:ss");
    qDebug() << "Back " << genTimeMinutes << " min Time : " << startProgBackTime.toString("d M yyyy hh:mm:ss");

    // ohlc for stable version
    ohlc = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(ohlc);
    //QCPFinancialDataMap data2 = QCPFinancial::timeSeriesToOhlc(volTime, volData, timeBinSize, 0); // startTime-60); // divide binSize by 3 just to make the ohlc bars a bit denser
    ohlc->setName("OHLC");
    ohlc->setChartStyle(QCPFinancial::csOhlc);
    //ohlc->setData(&data2, true);
    ohlc->setWidth(binSize*0.9); // 0.08);
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
    customPlot->xAxis->setAutoTickCount(10);
    //Через сколько отображать _тикет_ со временем на шкале X
    customPlot->xAxis->setTickStep(60); // 600 -> 10 минут
    //customPlot->xAxis->setRange(startTime, volTime.last() );

    customPlot->xAxis->scaleRange(1.0, customPlot->xAxis->range().center()); // Orig: 1.025
    customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());

    //customPlot->rescaleAxes();
    // make axis rects' left side line up:
    //QCPMarginGroup *group = new QCPMarginGroup(customPlot);
    //customPlot->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, group);

    // print debug
    //qDebug() << qFloor((volTime.first()-startTime)/timeBinSize+0.5);
    qDebug() << "--------------------------------------------------";
    // Start generate and update graph for 1 min interval
    connect(&timeAlign, SIGNAL(timeout()), this, SLOT(everySecSlot()));
    timeAlign.start(1000);

    //connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeMyDataSlot()));
    //dataTimer.start(1000); // Interval 1000 -> 1 second
    //dataTimer.start(60000); // interval -> 1 min



}


