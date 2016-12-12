#ifndef EXCHANGE_RANDOM_H
#define EXCHANGE_RANDOM_H

#include "exchange.h"

class Exchange_Random : public Exchange
{
    Q_OBJECT

public:
    Exchange_Random();

private:
    QList<DepthItem> *depthAsks;
    QList<DepthItem> *depthBids;

    QMap<double,double> lastDepthAsksMap;
    QMap<double,double> lastDepthBidsMap;

    void depthUpdateOrder(QString symbol, double price, double amount, bool isAsk);
};

#endif // EXCHANGE_RANDOM_H
