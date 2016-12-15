//  This file is part of Qt Bitcoin Trader
//      https://github.com/JulyIGHOR/QtBitcoinTrader
//  Copyright (C) 2013-2016 July IGHOR <julyighor@gmail.com>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  In addition, as a special exception, the copyright holders give
//  permission to link the code of portions of this program with the
//  OpenSSL library under certain conditions as described in each
//  individual source file, and distribute linked combinations including
//  the two.
//
//  You must obey the GNU General Public License in all respects for all
//  of the code used other than OpenSSL. If you modify file(s) with this
//  exception, you may extend this exception to your version of the
//  file(s), but you are not obligated to do so. If you do not wish to do
//  so, delete this exception statement from your version. If you delete
//  this exception statement from all source files in the program, then
//  also delete it here.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
            this->depthUpdateOrder(symbol,priceDouble,amount,true);
    }
    else
    {
        (*currentMap)[priceDouble]=amount;
        if(lastDepthBidsMap.value(priceDouble,0.0)!=amount)
            this->depthUpdateOrder(symbol,priceDouble,amount,false);
    }
}
// ------------------------------------------------------------------------------

// impl virtual
void Exchange_Random::getHistory(bool force)
{
    // Temp
    Q_UNUSED(force);
    /*
    //Orig code:
    if(tickerOnly)return;
    if(force)lastHistory.clear();
    if(!isReplayPending(208))sendToApi(208,"",true,true,"method=TradeHistory&");
    if(!isReplayPending(110))sendToApi(110,"info",false,true);
    */
}
// impl virtual
void Exchange_Random::buy(QString symbol, double apiBtcToBuy, double apiPriceToBuy)
{
    // Temp
    Q_UNUSED(symbol);
    Q_UNUSED(apiBtcToBuy);
    Q_UNUSED(apiPriceToBuy);
}
// impl virtual
void Exchange_Random::sell(QString symbol, double apiBtcToSell, double apiPriceToSell)
{
    // Temp
    Q_UNUSED(symbol);
    Q_UNUSED(apiBtcToSell);
    Q_UNUSED(apiPriceToSell);
}
// impl virtual
void Exchange_Random::cancelOrder(QString symbol, QByteArray order)
{
    // Temp
    Q_UNUSED(symbol);
    Q_UNUSED(order);
}
// ------------------------------------------------------------------------------
