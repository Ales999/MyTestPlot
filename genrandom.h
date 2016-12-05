#ifndef GENRANDOM_H
#define GENRANDOM_H

#include <QObject>
#include <QSharedDataPointer>

// My add
#include <QTimer>

class GenRandomData;

class GenRandom : public QObject
{
    Q_OBJECT

    QTimer  _tmr;       // таймер
    int     _int_timer; // Внутренний таймер

public:
    explicit GenRandom(QObject *parent = 0);
    GenRandom(const GenRandom &);
    GenRandom &operator=(const GenRandom &);
    ~GenRandom();

protected:
    void timerEvent(QTimerEvent *ev);

signals:
    void changed(const int &newCount);     // Сигнал "новые данные"
    void finished(void);    // Сигнал "остановка работы"

public slots:
    void terminateSlot();           // досрочная остановка
    void doActionSlot(void);

private slots:
    void doWorkSlot(void);

private:
    QSharedDataPointer<GenRandomData> data;
};

#endif // GENRANDOM_H
