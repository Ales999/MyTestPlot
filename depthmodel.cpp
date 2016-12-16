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

#include "depthmodel.h"
#include <QTimer>

DepthModel::DepthModel(bool isAskData)
{
    somethingChanged = true;
    isAsk=isAskData;
    originalIsAsk=isAsk;

    columnsCount = 0;
    groupedPrice = 0.0;
    groupedVolume = 0.0;

    QVector<int> qtemp1, qtemp2, qtemp3;
    qtemp1 << 1 << 2;
    qtemp2 << 4 << 5;
    qtemp3 << 3 << 8;

    dataset << qtemp1 << qtemp2 << qtemp3; // .insert(0, qtemp);
}

// ====================================================================================
//               Start implementation from base class 'QAbstractItemModel'
//

QModelIndex DepthModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))return QModelIndex();
    return createIndex(row,column);
}

QModelIndex DepthModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}

int DepthModel::rowCount(const QModelIndex &) const
{
    return dataset.size(); // .count(); // 8; // Simple test
    //return priceList.count()+grouped;
}

int DepthModel::columnCount(const QModelIndex &) const
{
    return 2; // Simple test
    //return columnsCount;
}
// Simple test, set header data
QVariant DepthModel::headerData( int nSection,
                                 Qt::Orientation orientation,
                                 int nRole ) const
{
    if( nRole == Qt::DisplayRole )
    {    // Если представление запрашивает надпись для горизонтального заголовка, то возвращаем строку
        if(orientation == Qt ::Horizontal) {
            switch( nSection )
            {
            case 0: return( QString( "property" ) );
            case 1: return( QString( "type" ) );
            case 2: return( QString( "value" ) );
            }
        } else // Иначе возвращаем номер секции
            return QString::number(nSection);
    }
    return QAbstractItemModel::headerData( nSection, orientation, nRole );
}

/*
QVariant DepthModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())return QVariant();
    int currentRow=index.row();

    if(role==Qt::WhatsThisRole)
    {
        //return baseValues.currentPair.currBSign+priceListStr.at(currentRow)+" "+baseValues.currentPair.currASign+volumeListStr.at(currentRow)+" "+baseValues.currentPair.currASign+sizeListStr.at(currentRow);
        return baseValues.currentPair.currBSign+priceList.at(currentRow)+" "+baseValues.currentPair.currASign+volumeList.at(currentRow)+" "+baseValues.currentPair.currASign+sizeList.at(currentRow);

    }

    if(role!=Qt::DisplayRole&&role!=Qt::ToolTipRole&&role!=Qt::StatusTipRole&&role!=Qt::ForegroundRole&&role!=Qt::BackgroundRole&&role!=Qt::TextAlignmentRole)return QVariant();

    int indexColumn=index.column();
    if(isAsk)indexColumn=columnsCount-indexColumn-1;

    if(role==Qt::TextAlignmentRole)
    {
        if(indexColumn==0)return 0x0081;
        if(indexColumn==1)return 0x0082;
        if(indexColumn==3)return 0x0082;
        return 0x0084;
    }

    if(grouped&&currentRow<2)
    {
        //?if(role==Qt::ForegroundRole)return baseValues.appTheme.black;
        if(currentRow==1||groupedPrice==0.0)return QVariant();
        QString firstRowText;
        switch(indexColumn)
        {
        case 0: //Price
                firstRowText=""; //?textFromDouble(groupedPrice);
                if(role==Qt::ToolTipRole)firstRowText.prepend(baseValues.currentPair.currBSign);
                break;
        case 1: //Volume
                firstRowText=""; //?textFromDouble(groupedVolume,baseValues.currentPair.currADecimals);
                if(role==Qt::ToolTipRole)firstRowText.prepend(baseValues.currentPair.currASign);
                break;
        }
        if(firstRowText.isEmpty())return QVariant();
        return firstRowText;
    }

    if(grouped)currentRow-=grouped;
    if(currentRow<0||currentRow>=priceList.count())return QVariant();

    if(!originalIsAsk)currentRow=priceList.count()-currentRow-1;

    if(role==Qt::StatusTipRole)
    {
        QString direction;

        switch(directionList.at(currentRow))
        {
        //?case -1: direction=downArrowStr+"\t"; break;
        //?case 1: direction=upArrowStr+"\t"; break;
        }
        return baseValues.currentPair.currBSign+priceList.at(currentRow)+"\t"+baseValues.currentPair.currASign+volumeList.at(currentRow)+"\t"+direction+baseValues.currentPair.currASign+sizeList.at(currentRow);
    }

    if(role==Qt::ForegroundRole)
    {
        if(indexColumn==1)
        {
            //?double volume=volumeList.at(currentRow);
            //?double smallValue=baseValues.currentPair.currAInfo.valueSmall;
            //?if(volume<=smallValue)return baseValues.appTheme.gray; smallValue*=10.0;
            //?if(volume<=smallValue)return baseValues.appTheme.black; smallValue*=10.0;
            //?if(volume<=smallValue)return baseValues.appTheme.darkGreen; smallValue*=10.0;
            //?if(volume<=smallValue)return baseValues.appTheme.darkRedBlue;
            //?return baseValues.appTheme.red;
        }
        return QVariant(); //?return baseValues.appTheme.black;
    }

    double requestedPrice=priceList.at(currentRow);
    if(requestedPrice<=0.0)return QVariant();

    if(role==Qt::BackgroundRole)
    {
        if(originalIsAsk)
        {
            //?if(mainWindow.ordersModel->currentAsksPrices.value(requestedPrice,false))return baseValues.appTheme.lightGreen;
        }
        else
        {
            //?if(mainWindow.ordersModel->currentBidsPrices.value(requestedPrice,false))return baseValues.appTheme.lightGreen;
        }
        return QVariant();
    }

    QString returnText;

    switch(indexColumn)
    {
    case 0://Price
        if(role==Qt::ToolTipRole)baseValues.currentPair.currBSign+priceList.at(currentRow);
        return priceList.at(currentRow);
        break;
    case 1:
        {//Volume
        if(volumeList.at(currentRow)<=0.0)return QVariant();
        if(role==Qt::ToolTipRole)baseValues.currentPair.currASign+volumeList.at(currentRow);
        return volumeList.at(currentRow);
        }
        break;
    case 2:
        {//Direction
            switch(directionList.at(currentRow))
            {
            //?case -1: return downArrow;
            //?case 1: return upArrow;
            default: return QVariant();
            }
        }
    case 3:
        {//Size
        //?if(sizeListGet(currentRow)<=0.0)return QVariant();
        //?if(role==Qt::ToolTipRole)baseValues.currentPair.currASign+sizeListStr.at(currentRow);
        //?return sizeListStr.at(currentRow);
        }
        break;
    default: break;
    }
    if(!returnText.isEmpty())return returnText;
    return QVariant();
}
*/

// ------------------
// Start Simple test
QVariant DepthModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    }
    else if (role == Qt::DisplayRole)
    {
        // problem solved, I forgot the Qt::EditRole
        return dataset[index.row()][index.column()];
    }
    else if(role == Qt::EditRole)
    {
        QString str = (QString)dataset[index.row()][index.column()];
        return str;
    }

    return QVariant();
}

bool DepthModel::setData(const QModelIndex &index,
                        const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        if (value.toString().isEmpty()) return false;
        dataset[index.row()][index.column()] = value.toInt();
        QModelIndex transposedIndex = createIndex(index.column(),
                                                  index.row());
        emit dataChanged(index, index);
        emit dataChanged(transposedIndex, transposedIndex);
        return true;
    }
    return false;
}

// End   Simple test
// ------------------

//               End   implementation from base class 'QAbstractItemModel'
// ========================================================================================

void DepthModel::setAsk(bool on)
{
    isAsk=on;
}

double &DepthModel::sizeListAt(int row)
{
    if(!originalIsAsk)return sizeList[sizeList.count()-row-1];
    return sizeList[row];
}

void DepthModel::sizeListRemoveAt(int row)
{
    if(!originalIsAsk)sizeList.removeAt(sizeList.count()-row-1);
    else
    sizeList.removeAt(row);
}

void DepthModel::reloadVisibleItems()
{
    QTimer::singleShot(100,this,SLOT(delayedReloadVisibleItems()));
}

void DepthModel::delayedReloadVisibleItems()
{
    emit dataChanged(index(0,0),index(priceList.count()-1,columnsCount-1));
}

void DepthModel::calculateSize()
{
    if(!somethingChanged)return;
    somethingChanged=true;

    double maxPrice=0.0;
    double maxVolume=0.0;
    double maxTotal=0.0;

    double totalSize=0.0;
    double totalPrice=0.0;

    if(originalIsAsk)
    {
        for(int n=0;n<priceList.count();n++)
        {
            int currentRow=n;
            if(!originalIsAsk)currentRow=priceList.count()-currentRow-1;

            totalSize+=volumeList.at(currentRow);
            totalPrice+=volumeList.at(currentRow)*priceList.at(currentRow);

            sizeListAt(currentRow)=totalSize;
            sizePriceList[currentRow]=totalPrice;
            //sizeListStr[currentRow]=textFromDouble(totalSize,qMin(baseValues.currentPair.currADecimals,baseValues.decimalsTotalOrderBook));

            maxPrice=qMax(maxPrice,priceList.at(currentRow));
            maxVolume=qMax(maxVolume,volumeList.at(currentRow));
            maxTotal=qMax(maxTotal,sizeListAt(currentRow));
        }
    }
    else
    {
        for(int n=priceList.count()-1;n>=0;n--)
        {
            int currentRow=n;
            if(originalIsAsk)currentRow=priceList.count()-currentRow-1;
            totalSize+=volumeList.at(currentRow);
            totalPrice+=volumeList.at(currentRow)*priceList.at(currentRow);
            sizeListAt(currentRow)=totalSize;
            sizePriceList[currentRow]=totalPrice;
            //sizeListStr[currentRow]=textFromDouble(totalSize,qMin(baseValues.currentPair.currADecimals,baseValues.decimalsTotalOrderBook));

            maxPrice=qMax(maxPrice,priceList.at(currentRow));
            maxVolume=qMax(maxVolume,volumeList.at(currentRow));
            maxTotal=qMax(maxTotal,sizeListAt(currentRow));
        }
    }

    //?widthPrice=10+textFontWidth(textFromDouble(maxPrice,baseValues.currentPair.priceDecimals));
    //?widthVolume=10+textFontWidth(textFromDouble(maxVolume,baseValues.currentPair.currADecimals));
    //?widthSize=10+textFontWidth(textFromDouble(maxTotal,baseValues.currentPair.currADecimals));

    //?widthPrice=qMax(widthPrice,widthPriceTitle);
    //?widthVolume=qMax(widthVolume,widthVolumeTitle);
    //?widthSize=qMax(widthSize,widthSizeTitle);

    int sizeColumn=2;
    if(isAsk)sizeColumn=1;
    emit dataChanged(index(0,sizeColumn),index(priceList.count()-1,sizeColumn));
}

void DepthModel::depthUpdateOrders(QList<DepthItem> *items)
{
    if(items==0)return;
    for(int n=0;n<items->count();n++) depthUpdateOrder( items->at(n) );
    delete items;
    calculateSize();
}


void DepthModel::depthUpdateOrder(DepthItem item)
{
    double price = item.price;
    if(price == 0.0) return;

    double volume = item.volume;
    int currentIndex = qLowerBound(priceList.begin(), priceList.end(), price) - priceList.begin();
    bool matchListRang = currentIndex>-1 && priceList.count()>currentIndex;

    if(volume==0.0)
    {//Remove item
        if(matchListRang)
        {
            beginRemoveRows(QModelIndex(), currentIndex+grouped, currentIndex+grouped);
            directionList.removeAt(currentIndex);
            priceList.removeAt(currentIndex);
            volumeList.removeAt(currentIndex);
            sizeListRemoveAt(currentIndex);
            sizePriceList.removeAt(currentIndex);
            //priceListStr.removeAt(currentIndex);
            //volumeListStr.removeAt(currentIndex);
            //sizeListStr.removeAt(currentIndex);
            endRemoveRows();
            somethingChanged=true;
        }
        return;
    }
    if(matchListRang && priceList.at(currentIndex)==price)
    {//Update
        if(volumeList.at(currentIndex)==volume) return;
        directionList[currentIndex]=volumeList.at(currentIndex)<volume?1:-1;
        volumeList[currentIndex]=volume;
        sizeListAt(currentIndex)=0.0;
        sizePriceList[currentIndex]=0.0;
        //priceListStr[currentIndex]=item.priceStr;
        //volumeListStr[currentIndex]=item.volumeStr;
        //sizeListStr[currentIndex]="0.0";
        somethingChanged=true;
        emit dataChanged(index(currentIndex+grouped,0),index(currentIndex+grouped,columnsCount-1));
    }
    else
    {//Insert
        beginInsertRows(QModelIndex(), currentIndex+grouped, currentIndex+grouped);
        priceList.insert(currentIndex,price);
        volumeList.insert(currentIndex,volume);
        sizeList.insert(currentIndex,volume);
        sizePriceList.insert(currentIndex,volume*price);
        directionList.insert(currentIndex,0);
        //priceListStr.insert(currentIndex,item.priceStr);
        //volumeListStr.insert(currentIndex,item.volumeStr);
        //sizeListStr.insert(currentIndex,item.volumeStr);
        endInsertRows();
        somethingChanged=true;
    }
}


