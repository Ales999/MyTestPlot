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
    qDebug()<<"From worker thread: " << QThread::currentThreadId();
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
    // qDebug() << "doActionSlot";
    emit changed( data->volTime.count() );

    // -------   START Timer(s) BLOCK --------------

    // В данном блоке представлено два подхода создания таймера

    //  Первый способ:
    // Используя внешний класс QTimer. Вызов работы - через SLOT - будет вызываться приватный слот 'doWorkSlot'

    // bool res;
    // res = QObject::connect (&_tmr, &QTimer::timeout, this, &GenRandom::doWorkSlot);	Q_ASSERT_X (res, "connect", "connection is not established");	// связывание внешнего таймера
    // _tmr.start(2*1000);     // запуск внешнего таймера ??? А зачем ?
    // thread()->sleep(1);     // выжидание 1 сек...
    // doWorkSlot();               // ... выдача состояния ...

    //  Второй способ:
    //  Через запуск встроенного таймера в классе c сохранением. Вызов работы - 'timerEvent' данного класса, в котором, в данном примере, будем напрямую вызывать 'doWorkSlot'

    _int_timer = startTimer(1*1000);     // ... и установка внутреннего таймера

    // -------   END   Timer BLOCK --------------

    // У каждого способа есть свои + и -
    // можно испоьзовать оба способа, но в каждом таймере нужно установить таймаут = 2 секунды, тогда они будут вызываться поочередно, для этого есть задержка в секунду: thread()->sleep(1);
}

void GenRandom::timerEvent(QTimerEvent *ev)
{   // внутренний таймер
    // На всякий проверим что это именно наш таймер
    if(ev->timerId() == _int_timer)
        doWorkSlot(); // private slot
    else
        QObject::timerEvent(ev);
}

void GenRandom::doWorkSlot() {
    // Gnerate random
    //qDebug() <<  "doWorkSlot: " << data->key ;
    data->key +=1;
    data->volTime.push_back( QDateTime::currentDateTime().toTime_t() );
    data->volData.push_back( (double)( qrand()/(double)RAND_MAX-0.5 )*3 );

    emit changed( data->volTime.count() ); // значения изменились

}
