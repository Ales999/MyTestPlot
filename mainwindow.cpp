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

    QDateTime start = QDateTime::currentDateTime(); //  QDateTime(QDate(2016, 11, 27));
    //start.setTimeSpec(Qt::UTC);
    double startTime = start.toLocalTime().toTime_t();

    //volTime.setSharable(true);
    //volData.setSharable(true);

    // Первый заброс данных во время и данные
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



    //static QTime time(QTime::currentTime());
    // calculate two new data points:
    //double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    double binSize = 600; //  3600*24; // bin data in 1 day intervals
/*
    // create candlestick chart:
    QCPFinancial *candlesticks = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
    candlesticks->setName("Candlestick");
    candlesticks->setChartStyle(QCPFinancial::csCandlestick);
    candlesticks->data()->set(QCPFinancial::timeSeriesToOhlc(volTime, volData, binSize, startTime));
     candlesticks->setWidth(binSize*0.85); //candlesticks->setWidth(binSize*0.9);
    candlesticks->setTwoColored(true);
    candlesticks->setBrushPositive(QColor(245, 245, 245));
    candlesticks->setBrushNegative(QColor(40, 40, 40));
    candlesticks->setPenPositive(QPen(QColor(0, 0, 0)));
    candlesticks->setPenNegative(QPen(QColor(0, 0, 0)));
*/



    // ohls for 2.0-beta
    QCPFinancial *ohlc = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
    ohlc->setName("OHLC");
    ohlc->setChartStyle(QCPFinancial::csOhlc);
    ohlc->data()->set(QCPFinancial::timeSeriesToOhlc(volTime, volData, binSize/10.0, startTime)); // divide binSize by 3 just to make the ohlc bars a bit denser
    ohlc->setWidth(binSize*0.08); // ohlc->setWidth(binSize*0.2);
    ohlc->setTwoColored(true);

/*
    // ohlc for stable version
    QCPFinancial *ohlc = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
    customPlot->addPlottable(ohlc);
    QCPFinancialDataMap data2 = QCPFinancial::timeSeriesToOhlc(volTime, volData, binSize/3.0, startTime); // divide binSize by 3 just to make the ohlc bars a bit denser
    ohlc->setName("OHLC");
    ohlc->setChartStyle(QCPFinancial::csOhlc);
    ohlc->setData(&data2, true);
    ohlc->setWidth(binSize*0.2);
    ohlc->setTwoColored(true);
*/


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

    //connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeMyDataSlot()));
    //dataTimer.start(1000); // Interval 0 means to refresh as fast as possible

    //QCPMarginGroup *group = new QCPMarginGroup(customPlot);
    //customPlot->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, group);
    //volumeAxisRect->setMarginGroup(QCP::msLeft|QCP::msRight, group);

}


void MainWindow::setupRealTimePlot(QCustomPlot *customPlot)
{
    demoName = "ReadTime Plot";

    // include this section to fully disable antialiasing for higher performance:
    /*
    customPlot->setNotAntialiasedElements(QCP::aeAll);
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    customPlot->xAxis->setTickLabelFont(font);
    customPlot->yAxis->setTickLabelFont(font);
    customPlot->legend->setFont(font);
    */



    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    customPlot->addGraph(); // red line
    customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setRange(-1.2, 1.2);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

///
/// \brief MainWindow::setupFinPlot - обычный статик данные
/// \param customPlot
///
void MainWindow::setupFinPlot(QCustomPlot *customPlot)
{
    demoName = "Finance";
    customPlot->legend->setVisible(true);

    // generate two sets of random walk data (one for candlestick and one for ohlc chart):
      int n = 500;
      QVector<double> time(n), value1(n), value2(n);
      QDateTime start = QDateTime(QDate(2016, 11, 27));
      start.setTimeSpec(Qt::UTC);
      double startTime = start.toTime_t();
      double binSize = 3600*24; // bin data in 1 day intervals
      time[0] = startTime;
      value1[0] = 60;
      value2[0] = 20;
      qsrand(9);
      for (int i=1; i<n; ++i)
      {
        time[i] = startTime + 3600*i;
        value1[i] = value1[i-1] + (qrand()/(double)RAND_MAX-0.5)*10;
        value2[i] = value2[i-1] + (qrand()/(double)RAND_MAX-0.5)*3;
      }
/*
      // create candlestick chart:
      QCPFinancial *candlesticks = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
      candlesticks->setName("Candlestick");
      candlesticks->setChartStyle(QCPFinancial::csCandlestick);
      candlesticks->data()->set(QCPFinancial::timeSeriesToOhlc(time, value1, binSize, startTime));
      candlesticks->setWidth(binSize*0.9);
      candlesticks->setTwoColored(true);
      candlesticks->setBrushPositive(QColor(245, 245, 245));
      candlesticks->setBrushNegative(QColor(40, 40, 40));
      candlesticks->setPenPositive(QPen(QColor(0, 0, 0)));
      candlesticks->setPenNegative(QPen(QColor(0, 0, 0)));
*/
      // create ohlc chart:
      QCPFinancial *ohlc = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
      ohlc->setName("OHLC");
      ohlc->setChartStyle(QCPFinancial::csOhlc);
      ohlc->data()->set(QCPFinancial::timeSeriesToOhlc(time, value2, binSize/3.0, startTime)); // divide binSize by 3 just to make the ohlc bars a bit denser
      ohlc->setWidth(binSize*0.2);
      ohlc->setTwoColored(true);

      /*
      // create bottom axis rect for volume bar chart:
      QCPAxisRect *volumeAxisRect = new QCPAxisRect(customPlot);
      customPlot->plotLayout()->addElement(1, 0, volumeAxisRect);
      volumeAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 100));
      volumeAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
      volumeAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
      // bring bottom and main axis rect closer together:
      customPlot->plotLayout()->setRowSpacing(0);
      volumeAxisRect->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msBottom);
      volumeAxisRect->setMargins(QMargins(0, 0, 0, 0));
      // create two bar plottables, for positive (green) and negative (red) volume bars:
      customPlot->setAutoAddPlottableToLegend(false);
      QCPBars *volumePos = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
      QCPBars *volumeNeg = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
      for (int i=0; i<n/5; ++i)
      {
        int v = qrand()%20000+qrand()%20000+qrand()%20000-10000*3;
        (v < 0 ? volumeNeg : volumePos)->addData(startTime+3600*5.0*i, qAbs(v)); // add data to either volumeNeg or volumePos, depending on sign of v
      }
      volumePos->setWidth(3600*4);
      volumePos->setPen(Qt::NoPen);
      volumePos->setBrush(QColor(100, 180, 110));
      volumeNeg->setWidth(3600*4);
      volumeNeg->setPen(Qt::NoPen);
      volumeNeg->setBrush(QColor(180, 90, 90));

      // interconnect x axis ranges of main and bottom axis rects:
      connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), volumeAxisRect->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
      connect(volumeAxisRect->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis, SLOT(setRange(QCPRange)));
*/


      // configure axes of both main and bottom axis rect:
      QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
      dateTimeTicker->setDateTimeSpec(Qt::UTC);
      dateTimeTicker->setDateTimeFormat("dd. MMMM");
      //volumeAxisRect->axis(QCPAxis::atBottom)->setTicker(dateTimeTicker);
      //volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelRotation(15);
      customPlot->xAxis->setBasePen(Qt::NoPen);
      customPlot->xAxis->setTickLabels(false);
      customPlot->xAxis->setTicks(false); // only want vertical grid in main axis rect, so hide xAxis backbone, ticks, and labels
      customPlot->xAxis->setTicker(dateTimeTicker);
      customPlot->rescaleAxes();
      customPlot->xAxis->scaleRange(1.025, customPlot->xAxis->range().center());
      customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());

      // make axis rects' left side line up:
      //QCPMarginGroup *group = new QCPMarginGroup(customPlot);
      //customPlot->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, group);
      //volumeAxisRect->setMarginGroup(QCP::msLeft|QCP::msRight, group);



}
