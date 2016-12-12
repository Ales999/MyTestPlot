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
