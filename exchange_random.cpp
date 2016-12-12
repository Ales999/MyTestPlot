#include "exchange_random.h"

Exchange_Random::Exchange_Random()
{
    moveToThread(this);
}

void Exchange_Random::depthUpdateOrder(QString symbol, double price, double amount, bool isAsk)
{
    if(symbol!=baseValues.currentPair.symbol)return;

    if(isAsk)
    {
        if(depthAsks==0)return;
        DepthItem newItem;
        newItem.price=price;
        newItem.volume=amount;
        if(newItem.isValid())
            (*depthAsks)<<newItem;
    }
    else
    {
        if(depthBids==0)return;
        DepthItem newItem;
        newItem.price=price;
        newItem.volume=amount;
        if(newItem.isValid())
            (*depthBids)<<newItem;
    }
}

void Exchange_Random::depthSubmitOrder(QString symbol, QMap<double, double> *currentMap, double priceDouble, double amount, bool isAsk)
{
    if(symbol!=baseValues.currentPair.symbol)return;

    if(priceDouble==0.0||amount==0.0)return;

    if(isAsk)
    {
        (*currentMap)[priceDouble]=amount;
        if(lastDepthAsksMap.value(priceDouble,0.0)!=amount)
            depthUpdateOrder(symbol,priceDouble,amount,true);
    }
    else
    {
        (*currentMap)[priceDouble]=amount;
        if(lastDepthBidsMap.value(priceDouble,0.0)!=amount)
            depthUpdateOrder(symbol,priceDouble,amount,false);
    }
}

void Exchange_Random::buy(QString, double, double)
{

}

void Exchange_Random::sell(QString, double, double)
{

}
