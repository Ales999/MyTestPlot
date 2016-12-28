#include "testplotpresenter.h"
#include "itestplotview.h"

#include "main.h"

// https://habrahabr.ru/post/107698/

TestPlotPresenter::TestPlotPresenter(ITestPlotView *view, QObject *parent)
    : QObject(parent), m_model(new TestPlotModel), m_view(view)
{
    qDebug("Created TestPlotPresenter\n");

    //QObject *view_obj = dynamic_cast<QObject*>(m_view);
    //QObject::connect(view_obj, SIGNAL(okActionTriggered()), this, SLOT(processOkAction()));

    tp_int_timer = startTimer(0);

}

void TestPlotPresenter::refreshView() const
{
    qDebug() << "Do refreshView";

}

void TestPlotPresenter::timerEvent(QTimerEvent *ev)
{
    qDebug() << "Timer ID:" << ev->timerId();
    if( ev->timerId() == tp_int_timer)
    {
        bool res;
        // Остановка таймера
        killTimer(ev->timerId());
        // установка связей с объектом
        res = QObject::connect(&gr_obj, SIGNAL(objectIsReady()), this, SLOT(gr_doConnectObjectSlot())); Q_ASSERT_X (res, "connect", "connection is not established");
        // запуск потока с высоким приоритетом
        gr_obj.starting( SIGNAL( finished() ), SLOT( doTerminateSlot() ), QThread::HighPriority );
    } else
        QObject::timerEvent(ev);
}

void TestPlotPresenter::gr_terminateSlot()
{
    qDebug() << "gr_terminateSlot";
    emit finished ();
}

#include "randtwister.h"

void TestPlotPresenter::gr_doChangedSlot(const QMap<double, double> &newData)
{
    double twrand =0.0;
    QString strKey ="";
    QString toSend;         // Что будем отправлять в окно
    RandTwister *twist = new RandTwister();

    //uint32_t _tw = twist->ExtractU32();
    // Shift, example, '>> 13': 3645644232 ---> 445024
    //ptrdiff_t l_twr = ptrdiff_t(_tw) >> 13;
    //uint32_t l_twr = _tw >> 13;
    //l_twr/100000000
    twrand =  twist->GetRandVolume();

    QString twstr =QString::number(twrand,'g',8);
    delete twist;

    if( !newData.isEmpty())
    {
        double  dataVol;
        strKey = QDateTime::fromTime_t( newData.firstKey() ).toString( baseValues.timeFormat );
        dataVol = newData.value(newData.firstKey());
        //qDebug() << "gr_doChangedSlot: " << QDateTime::fromTime_t( newData.firstKey() ).toUTC().toString("hh:mm:ss")  << " : " << newData.value(newData.firstKey()) ;

        QTextStream(&toSend) << "TimeKey: " << strKey << " Data: " << dataVol << "\tRandom number: " << twstr ;

        m_view->setStatusBarMassage(toSend);

    } else
        qDebug() << "newData is Empty !";

//    ui->statusBar->showMessage(
//      QString("Key: %1 Value: %2")
//                .arg( strKey )
//                .arg( dataVol)
//                ,0);

}

void TestPlotPresenter::gr_doConnectObjectSlot()
{
    qDebug() << "gr_doConnectObjectSlot";
    bool res;

    res = QObject::connect (this, &TestPlotPresenter::gr_startAction,  gr_obj, &GenRandom::doActionSlot); Q_ASSERT_X (res, "connect", "connection is not established");	// установка сигнала запуска действия
    res = QObject::connect (this, &TestPlotPresenter::finished,  gr_obj, &GenRandom::doTerminateSlot);    Q_ASSERT_X (res, "connect", "connection is not established");	// закрытие этого объекта хакрывает объект в потоке

    res = QObject::connect (gr_obj, &GenRandom::finished, this, &TestPlotPresenter::finished);            Q_ASSERT_X (res, "connect", "connection is not established");	// конец операции завершает работу приложения
    res = QObject::connect (gr_obj, &GenRandom::changed,  this, &TestPlotPresenter::gr_doChangedSlot);    Q_ASSERT_X (res, "connect", "connection is not established");	// установка значения в данном потоке

    //res = QObject::connect (&_btn, &QPushButton::clicked, _obj, &Operation::terminate);		Q_ASSERT_X (res, "connect", "connection is not established");	// остановка работы потока

    emit gr_startAction(); // Запуск действия


}
