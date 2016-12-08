#ifndef MAIN_H
#define MAIN_H

#include <QString>

#define grouped (baseValues_->groupPriceValue>0.0?2:0)


struct BaseValues
{
    void Construct();
    double groupPriceValue;

    QString timeFormat;
    QString dateTimeFormat;
};

#define baseValues (*baseValues_)
extern BaseValues *baseValues_;

#endif // MAIN_H
