#ifndef GENRANDOM_H
#define GENRANDOM_H

#include <QObject>
#include <QSharedDataPointer>

// My add
#include <QTimer>

typedef QMap<double, double> NewGenData;

class GenRandomData;

class GenRandom : public QObject
{
    Q_OBJECT

    QTimer  _tmr;       // таймер
    int     _int_timer; // ID Внутреннего таймера

signals:
    void changed(const NewGenData &newData);      // Сигнал "новые данные"
    void finished(void);                    // Сигнал "остановка работы"

public slots:
    void doTerminateSlot();                   // досрочная остановка
    void doActionSlot(void);

private slots:
    void doWorkSlot(void);

public:
    explicit GenRandom(QObject *parent = 0);
    GenRandom(const GenRandom &);
    GenRandom &operator=(const GenRandom &);
    ~GenRandom();

protected:
    void timerEvent(QTimerEvent *ev);

private:
    QSharedDataPointer<GenRandomData> data;
};

#endif // GENRANDOM_H

