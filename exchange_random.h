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
    void depthSubmitOrder(QString symbol, QMap<double,double> *currentMap ,double priceDouble, double amount, bool isAsk);

public slots:
    void buy(QString, double, double);
    void sell(QString, double, double);
};

#endif // EXCHANGE_RANDOM_H
