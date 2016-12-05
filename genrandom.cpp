#include "genrandom.h"
#include "threadedobject.h"

// * ---- Start default

// Мой закрытый класс с данными
class GenRandomData : public QSharedData
{
public:

    double key;
};

GenRandom::GenRandom(QObject *parent) : QObject(parent), data(new GenRandomData)
{

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

}
// * ---- End default

void GenRandom::terminate()
{
    killTimer(_int_timer);
    _tmr.stop();
    //delete data; ??
    data->key= 0;
    emit finished();
}

void GenRandom::doActionSlot()
{
    bool res;
    // emit change
    res = QObject::connect (&_tmr, &QTimer::timeout, this, &GenRandom::doWorkSlot);	Q_ASSERT_X (res, "connect", "connection is not established");	// связывание внешнего таймера
    _tmr.start(1*1000);     // запуск внешнего таймера
    thread()->sleep(1);     // выжидание 1 сек...
    doWorkSlot();               // ... выдача состояния ...
    startTimer(1*1000);     // ... и установка внутреннего таймера
}

void GenRandom::timerEvent(QTimerEvent *ev)
{   // внутренний таймер
    if(ev->timerId() == _int_timer) doWorkSlot(); // private slot
    else QObject::timerEvent(ev);
}

void GenRandom::doWorkSlot() {
    // Gnerate random
    data->key +=1;
}
