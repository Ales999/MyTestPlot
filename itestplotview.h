#ifndef ITESTPLOTVIEW_H
#define ITESTPLOTVIEW_H

#include "testplotmodel.h"
#include "depthmodel.h"

// Это иннтерфейс
// https://habrahabr.ru/post/107698/


class ITestPlotView
{
public:
    // http://stackoverflow.com/questions/23306790/why-am-i-getting-undefined-symbols-typeinfo-vtable-with-a-virtual-and
    virtual void setStatusBarMessage(QString message) const = 0;
                                                        // ^^^^ making it pure virtual
    virtual void setAskTable(DepthModel *askModel) const = 0;
    virtual void setBidTable(DepthModel *bidModel) const = 0;
    // fore test
    virtual void setAskTable(QAbstractItemModel *model) const = 0;

public: // signals
    //virtual void calcActionTriggered() = 0;

};

#endif // ITESTPLOTVIEW_H
