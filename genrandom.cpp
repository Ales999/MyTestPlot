#include "genrandom.h"
#include "threadedobject.h"

// * ---- Start default

// Мой закрытый класс с данными
class GenRandomData : public QSharedData
{
public:

    double key;
    QVector<double> volTime;
    QVector<double> volData;
};

GenRandom::GenRandom(QObject *parent) : QObject(parent), data(new GenRandomData)
{
    data->key = 0;
}

GenRandom::GenRandom(const GenRandom &rhs) : data(rhs.data)
{

}

GenRandom &GenRandom::operator=(const GenRandom &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

GenRandom::~GenRandom()
{
    //qDebug() << "delete Random";
}
// * ---- End default

void GenRandom::terminateSlot()
{
    _tmr.stop();
    killTimer(_int_timer);
    //delete data; ??
    data->volTime.clear();
    data->volData.clear();
    data->key= 0;
    emit finished();
}

void GenRandom::doActionSlot()
{
    bool res;
    emit changed( data->volTime.count() );
    res = QObject::connect (&_tmr, &QTimer::timeout, this, &GenRandom::doWorkSlot);	Q_ASSERT_X (res, "connect", "connection is not established");	// связывание внешнего таймера
    //qDebug() << "doActionSlot";
    _tmr.start(1*1000);     // запуск внешнего таймера
    thread()->sleep(1);     // выжидание 1 сек...
    doWorkSlot();               // ... выдача состояния ...
    _int_timer = startTimer(1*1000);     // ... и установка внутреннего таймера
}

void GenRandom::timerEvent(QTimerEvent *ev)
{   // внутренний таймер
    if(ev->timerId() == _int_timer) doWorkSlot(); // private slot
    else QObject::timerEvent(ev);
}

void GenRandom::doWorkSlot() {
    // Gnerate random
    data->key +=1;
    data->volTime.push_back( QDateTime::currentDateTime().toTime_t() );
    data->volData.push_back( (double)( qrand()/(double)RAND_MAX-0.5 )*3 );

    emit changed( data->volTime.count() ); // значения изменились

}
