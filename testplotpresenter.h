#ifndef TESTPLOTPRESENTER_H
#define TESTPLOTPRESENTER_H

#include <QObject>
#include "threadedobject.h"
#include "genrandom.h"
#include "testplotmodel.h"

class ITestPlotView;

class TestPlotPresenter : public QObject
{
    Q_OBJECT

    ThreadedObject <GenRandom>	gr_obj;         // В отдельном потоке - генерация данных

public:
    explicit TestPlotPresenter (ITestPlotView *view, QObject *parent = 0);

private:
    void refreshView() const;

    TestPlotModel *m_model;
    ITestPlotView *m_view;

protected:
    int tp_int_timer;                           // ID внутреннего одноразового таймера
    void timerEvent (QTimerEvent *ev);

// Сигнал вырабатывается когда происходит определенное событие
signals:
    void gr_startAction (void);                 // сигнал "запуск действия"
    void finished (void);                      // сигнал "завершение работы"

// Слот это функция, которая вызывается в ответ на определенный сигнал.
public slots:
    void gr_terminateSlot (void);               // завершение работы приложения

private slots:
    void gr_doChangedSlot(const QMap<double, double> &newData); // Появились новые данные
    void gr_doConnectObjectSlot (void);         // установка связей с объектом

};

#endif // TESTPLOTPRESENTER_H
