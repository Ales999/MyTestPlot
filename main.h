#ifndef MAIN_H
#define MAIN_H

#include <QString>

struct BaseValues
{
    void Construct();
    QString timeFormat;
    QString dateTimeFormat;
};

#define baseValues (*baseValues_)
extern BaseValues *baseValues_;

#endif // MAIN_H
