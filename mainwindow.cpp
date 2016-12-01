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
    ui->customPlot->setVisible(false);
    setupRealMyTimePlot( ui->customPlot );
    setWindowTitle("QCustomPlot: "+demoName);
    statusBar()->clearMessage();
    ui->customPlot->replot();
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
    qDebug() << "Current PC Time    " << QTime::currentTime().toString("hh:mm:ss");

    this->startTime += 60;
    qDebug() << "this->startTime:   " << QDateTime::fromTime_t(this->startTime).toString("hh:mm:ss.");

    InitRandomData(loTime, loData, this->startTime );

    qDebug() << "loTime Count:      " << loTime.count();
    qDebug() << "New Time First:    " << QDateTime::fromTime_t( loTime.first() ).toString("hh:mm:ss.");
    qDebug() << "New Timee Last:    " << QDateTime::fromTime_t( loTime.last()  ).toString("hh:mm:ss.");

    QCPFinancialDataMap dataNew = QCPFinancial::timeSeriesToOhlc(loTime, loData, this->timeBinSize, 0);

    QMap<double,QCPFinancialData>::iterator it = dataNew.begin();
    for(;it != dataNew.end(); ++it)
        qDebug() << QDateTime::fromTime_t( it.key()  ).toString("hh:mm:ss.");

    // Add local temp new data/time
    ohlc->addData( dataNew );

    // Add local time/date to global time/data and clean old
    this->volTime.append(loTime);
    this->volData.append(loData);

    for ( int l=0; l<60; l++)
    {
        volTime.removeFirst();
        volData.removeFirst();
        this->graphStartTime += 1;
    }
    // Set Axis size for global time/data
    ui->customPlot->xAxis->setRange( volTime.first(), volTime.last() );

    qDebug() << "Update Time:       " << QDateTime::fromTime_t(this->startTime).toString("hh:mm:ss.");
    qDebug() << "Time Count:        " << volTime.count() << "Data Count: "  << volData.count();
    qDebug() << "All Time First:    " << QDateTime::fromTime_t( volTime.first() ).toString("hh:mm:ss.");
    qDebug() << "All Time Last:     " << QDateTime::fromTime_t( volTime.last()  ).toString("hh:mm:ss.");

    ui->customPlot->replot();
    ui->customPlot->rescaleAxes();
    qDebug() << "--------------------------------------------------";
}

void MainWindow::InitRandomData(QVector<double> &ivolTime, QVector<double> &ivolData, double lostartTime)
{
    for(int msec = 0; msec < 60; msec++ )
    {
        ivolTime.push_back( lostartTime ); // add time to ivolTime
        lastPush += my_rand(); // add random data to ivolData
        ivolData.push_back( lastPush );

        lostartTime += 1; // Add One second
    }

}

void MainWindow::InitRandomData(QVector<double> &ivolTime, QVector<double> &ivolData, double lostartTime, uint minuteGen)
{
    bool firstMin = true;
    uint mingen = 0;
    do
    {
        for(int msec = 0; msec <= 60; msec++ )
        {
            if ( !volTime.isEmpty() && !volData.isEmpty() && firstMin )
            {
                ivolTime.push_back( lostartTime );
                ivolData.push_back( lastPush );
                firstMin = false;
            } else
            {
                ivolTime.push_back( lostartTime ); // add time to volTime
                lastPush += my_rand(); // add random data to volData
                ivolData.push_back( lastPush );
            }
            lostartTime += 1; // Add One second
        }
        firstMin = true;
        mingen++;
        lostartTime += 1;

    } while(mingen < minuteGen);
}



void MainWindow::setupRealMyTimePlot(QCustomPlot *customPlot)
{
    demoName = "Моя проба";

    double binSize = 60; // 600 --> 10 Min, 3600*24; --> bin data in 1 day intervals
    this->timeBinSize = binSize; //10 /// 5- > В каждой 10-ти минутке по 5 баров

    qDebug() << "Start Program Time: " << QDateTime::currentDateTime().toString("d M yyyy hh:mm:ss");

    // ohlc for stable version
    ohlc = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(ohlc);
    ohlc->setName("OHLC");
    ohlc->setChartStyle(QCPFinancial::csOhlc);
    ohlc->setWidth(binSize*0.9); // 0.08);
    ohlc->setTwoColored(true);
    // bring bottom and main axis rect closer together:
    customPlot->plotLayout()->setRowSpacing(0);
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    customPlot->xAxis->setTickLabelRotation(15);
    customPlot->xAxis->setAutoTickStep(false);
    customPlot->xAxis->setAutoTickCount(10);
    //Через сколько отображать _тикет_ со временем на шкале X
    customPlot->xAxis->setTickStep(60); // 600 -> 10 минут

    customPlot->xAxis->scaleRange(1.0, customPlot->xAxis->range().center()); // Orig: 1.025
    customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());

    qDebug() << "--------------------------------------------------";
    // Start generate and update graph for 1 min interval
    connect(&timeAlign, SIGNAL(timeout()), this, SLOT(everySecSlot()));
    timeAlign.start(1000);


}


