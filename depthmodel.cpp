#include "depthmodel.h"

DepthModel::DepthModel(bool isAskData)
{
    somethingChanged = true;
    isAsk=isAskData;
    originalIsAsk=isAsk;

    columnsCount = 0;
    groupedPrice = 0.0;
    groupedVolume = 0.0;
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
    return priceList.count()+grouped;
}

int DepthModel::columnCount(const QModelIndex &) const
{
    return columnsCount;
}

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
            double volume=volumeList.at(currentRow);
            double smallValue=baseValues.currentPair.currAInfo.valueSmall;
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

// ========================================================================================

void DepthModel::setAsk(bool on)
{
    isAsk=on;
}

void DepthModel::depthUpdateOrders(QList<DepthItem> *items)
{
    if(items==0)return;
    for(int n=0;n<items->count();n++) depthUpdateOrder( items->at(n) );
    delete items;
    //calculateSize();  // TODO: implement and enable this line
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


