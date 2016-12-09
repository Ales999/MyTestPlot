#ifndef MAIN_H
#define MAIN_H

#include <QString>
#include <QMap>
#include <qmetatype.h>

#define grouped (baseValues_->groupPriceValue>0.0?2:0)

#include "currencyinfo.h"
#include "currencypairitem.h"

struct BaseValues
{
    void Construct();
    double groupPriceValue;

    QString timeFormat;
    QString dateTimeFormat;
    // Торгуемая Пара
    CurrencyPairItem currentPair;
    // Список торгуемых пар с ключем по имени
    QMap<QString,CurencyInfo> currencyMap;
};

#define baseValues (*baseValues_)
extern BaseValues *baseValues_;

#endif // MAIN_H
