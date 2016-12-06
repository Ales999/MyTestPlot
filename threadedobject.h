#ifndef THREADEDOBJECT_H
#define THREADEDOBJECT_H

//
//  Get from https://habrahabr.ru/post/203254/
//
#include <QtCore>

// **
// **  Базовый класс для потока
// **

class ThreadedObjectBase: public QThread
{
    Q_OBJECT

protected:
    const char *_finished_signal;		// имя сигнала "окончание работы объекта"
    const char *_terminate_slot;		// имя слота "остановка работы"
    bool _to_delete_later_thread;
    bool _to_delete_later_object;		// установка отложенного удаление объекта

    // . настройка
    void initObject (QObject *obj)
    {
        bool res;
        if (_finished_signal)		// установить сигнал "окончание работы объекта"?
        {	res = connect (obj, _finished_signal, this, SLOT (quit ()));			Q_ASSERT_X (res, "connect", "connection is not established");	}	// по окончанию работы объекта поток будет завершен
        if (_terminate_slot)		// установить слот "остановка работы"?
        {	res = connect (this, SIGNAL (finished ()), obj, _terminate_slot);	Q_ASSERT_X (res, "connect", "connection is not established");	}	// перед остановкой потока будет вызван слот объекта "остановка работы"
        if (_to_delete_later_object && _finished_signal)	// установить отложенное удаление объекта?
        {	res = connect (obj, _finished_signal, obj, SLOT (deleteLater ()));	Q_ASSERT_X (res, "connect", "connection is not established");	}	// по окончанию работы объекта будет установлено отложенное удаление
        emit objectIsReady ();		// объект готов к работе
    }

public:
    ThreadedObjectBase (QObject *parent = 0): QThread (parent){}

signals:
    void objectIsReady (void);			// сигнал "объект запущен"
};	// class ThreadedObject

// **
// **  Шаблонный класс для потока
// **

template <class T>
class ThreadedObject: public ThreadedObjectBase
{
protected:
    T	*_obj;		// объект, исполняемый в новом потоке

public:
    ThreadedObject (QObject *parent = 0): ThreadedObjectBase (parent), _obj (0)	{}

    // . настройка
    void starting (const char *FinishedSignal = 0, const char *TerminateSlot = 0, QThread::Priority Priority = QThread::InheritPriority, bool ToDeleteLaterThread = true, bool ToDeleteLaterObject = true)		// запуск нового потока
    {
        _finished_signal = FinishedSignal;		// запоминание имени сигнала "окончание работы объекта"
        _terminate_slot = TerminateSlot;		// запоминание имени слота "остановка работы"
        _to_delete_later_thread = ToDeleteLaterThread;
        _to_delete_later_object = ToDeleteLaterObject;	// запоминание установки отложенного удаление объекта
        start (Priority);	// создание объекта
    }

    void run (void)	{ initObject (_obj = new T); exec (); }		// создание объекта

    // . состояние
    bool objectIsCreated (void) const	{ return _obj != 0; }							// объект готов к работе?

    T* ptr (void) 						{ return reinterpret_cast <T*> (_obj); }			// указатель на объект
    const T* cptr (void) const			{ return reinterpret_cast <const T*> (_obj); }		// указатель на константный объект

    // . перегрузки
    operator T* (void)					{ return ptr (); }		// указатель на объект
    T* operator -> (void)				{ return ptr (); }		// указатель на объект
    operator const T* (void) const		{ return cptr (); }		// указатель на константный объект
    const T* operator -> (void) const	{ return cptr (); }		// указатель на константный объект
};	// class ThreadedObject


#endif // THREADEDOBJECT_H
