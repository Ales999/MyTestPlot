#ifndef ITESTPLOTVIEW_H
#define ITESTPLOTVIEW_H

#include "testplotmodel.h"

// Это иннтерфейс
// https://habrahabr.ru/post/107698/


class ITestPlotView
{
public:
    // http://stackoverflow.com/questions/23306790/why-am-i-getting-undefined-symbols-typeinfo-vtable-with-a-virtual-and
    virtual void setStatusBarMassage(QString message) const = 0;
                                                        // ^^^^ making it pure virtual

public: // signals
    //virtual void calcActionTriggered() = 0;

};

#endif // ITESTPLOTVIEW_H
