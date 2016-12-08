#include "depthmodel.h"

DepthModel::DepthModel(bool isAskData)
{
    somethingChanged = true;
    isAsk=isAskData;
    originalIsAsk=isAsk;
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
    // ....
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


