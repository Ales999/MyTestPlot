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
    // 1/2 minute shift
    int secShift = 30;
    QTime sqtime(QTime::currentTime());

    if( sqtime.second() == secShift )
    {
        if (First )
        {
            First = false;
            ui->customPlot->setVisible(true);
            ui->waitingLabel->setVisible(false);
            QDateTime setupTime = QDateTime(QDate::currentDate(), sqtime );
            setupTime.setTimeSpec(Qt::UTC);
            QDateTime startProgBackTime = setupTime.addSecs( 0-(genTimeMinutes*60) );
            qDebug() << "First Time:            " << setupTime.toString("hh:mm:ss") << "Reverse Time " << genTimeMinutes << "Min:" << startProgBackTime.toString("hh:mm:ss");

            this->startTime         = (setupTime.toTime_t()) - secShift*2;
            this->graphStartTime    = startProgBackTime.toTime_t();


            InitRandomData(volTime, volData, graphStartTime, genTimeMinutes );

            QCPFinancialDataMap data2 = QCPFinancial::timeSeriesToOhlc(volTime, volData, timeBinSize, 0);
            // Debug output
            QMap<double,QCPFinancialData>::iterator it = data2.begin();
            for(;it != data2.end(); ++it)
                qDebug() << "Gen keys:              " << QDateTime::fromTime_t( it.key()  ).toUTC().toString("hh:mm:ss");

            ohlc->setData(&data2, true);
            ui->customPlot->rescaleAxes();
            ui->customPlot->replot();
        } else
            QTimer::singleShot(0, this, SLOT(realtimeMyDataSlot()));
    }
    // Update graphics
    if (sqtime.second() == 0)
        ui->customPlot->replot();

}

void MainWindow::realtimeMyDataSlot()
{

    QVector<double> loTime, loData;
    qDebug() << "Current PC Time        " << QTime::currentTime().toString("hh:mm:ss");

    this->startTime += 60;
    qDebug() << "this->startTime:       " << QDateTime::fromTime_t(this->startTime).toUTC().toString("hh:mm:ss");

    InitRandomData(loTime, loData, this->startTime );

    qDebug() << "R/T Time Count:        " << loTime.count();
    qDebug() << "R/T Time First:        " << QDateTime::fromTime_t( loTime.first() ).toUTC().toString("hh:mm:ss");
    qDebug() << "R/T Time Last:         " << QDateTime::fromTime_t( loTime.last()  ).toUTC().toString("hh:mm:ss");

    QCPFinancialDataMap dataNew = QCPFinancial::timeSeriesToOhlc(loTime, loData, this->timeBinSize, 0);

    QMap<double,QCPFinancialData>::iterator it = dataNew.begin();
    int numint =0;
    for(;it != dataNew.end(); ++it) {
        qDebug( "OHLC[%d] keys:           \"%s\"", numint, qPrintable( QDateTime::fromTime_t( it.key()  ).toUTC().toString("hh:mm:ss") ) );
        numint += 1;
    }

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

    qDebug() << "Update Time:           " << QDateTime::fromTime_t(this->startTime).toUTC().toString("hh:mm:ss");
    qDebug() << "All Time Vec Count:    " << volTime.count() << "Data Count: "  << volData.count();
    qDebug() << "All Time Vec First:    " << QDateTime::fromTime_t( volTime.first() ).toUTC().toString("hh:mm:ss");
    qDebug() << "All Time Vec Last:     " << QDateTime::fromTime_t( volTime.last()  ).toUTC().toString("hh:mm:ss");

    //ui->customPlot->replot();
    ui->customPlot->rescaleAxes();
    qDebug() << "--------------------------------------------------";
}

void MainWindow::InitRandomData(QVector<double> &ivolTime, QVector<double> &ivolData, double lostartTime)
{
    //lostartTime += 1;
    for(int msec = 1; msec <= 60; msec++ )
    {
        ivolTime.push_back( lostartTime ); // add time to ivolTime
        if (msec == 1)
        {   // Need for close == open next OHLC
            ivolData.push_back( lastPush );
        } else {
            lastPush += my_rand(); // add random data to ivolData
            ivolData.push_back( lastPush );
        }

        lostartTime += 1; // Add One second
    }

}

void MainWindow::InitRandomData(QVector<double> &ivolTime, QVector<double> &ivolData, double lostartTime, uint minuteGen)
{
    bool firstMin = true;
    uint mingen = 0;
    do
    {
        for(int msec = 1; msec <= 60; msec++ )
        {
            // set _last_ data every one min
            if ( firstMin )
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
        //lostartTime += 1;

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
    customPlot->xAxis->setDateTimeSpec(Qt::UTC);

    customPlot->xAxis->setTickLabelRotation(15);
    customPlot->xAxis->setAutoTickStep(false);
    customPlot->xAxis->setAutoTickCount(10);
    customPlot->xAxis->setAutoSubTicks(5);
    //Через сколько отображать _тикет_ со временем на шкале X
    customPlot->xAxis->setTickStep(60); // 600 -> 10 минут
    customPlot->xAxis->setSubTickCount(6);


    customPlot->xAxis->scaleRange(1.025, customPlot->xAxis->range().center()); // Orig: 1.025
    customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());

    qDebug() << "------------------ END Setup Plot ---------------------";
    // Start generate and update graph for 1 min interval
    connect(&timeAlign, SIGNAL(timeout()), this, SLOT(everySecSlot()));
    timeAlign.start(1000);


}

// My Dev version
QCPFinancialDataMap MainWindow::timeSeriesToOhlcOne(const QVector<double> &time, const QVector<double> &value, double timeBinSize, double timeBinOffset)
{
  QCPFinancialDataMap map;
  int count = qMin(time.size(), value.size());
  if (count == 0)
    return QCPFinancialDataMap();

  QCPFinancialData currentBinData(0, value.first(), value.first(), value.first(), value.first());
  int currentBinIndex = qFloor((time.first()-timeBinOffset)/timeBinSize+0.5);
  for (int i=0; i<count; ++i)
  {
    int index = qFloor((time.at(i)-timeBinOffset)/timeBinSize+0.5);
    if (currentBinIndex == index) // data point still in current bin, extend high/low:
    {
      if (value.at(i) < currentBinData.low) currentBinData.low = value.at(i);
      if (value.at(i) > currentBinData.high) currentBinData.high = value.at(i);
      if (i == count-1) // last data point is in current bin, finalize bin:
      {
        currentBinData.close = value.at(i);
        currentBinData.key = timeBinOffset+(index)*timeBinSize;
        map.insert(currentBinData.key, currentBinData);
      }
    } else // data point not anymore in current bin, set close of old and open of new bin, and add old to map:
    {
      // finalize current bin:
      currentBinData.close = value.at(i-1);
      currentBinData.key = timeBinOffset+(index-1)*timeBinSize;
      map.insert(currentBinData.key, currentBinData);
      // start next bin:
      currentBinIndex = index;
      currentBinData.open = value.at(i);
      currentBinData.high = value.at(i);
      currentBinData.low = value.at(i);
    }
  }

  return map;
}
