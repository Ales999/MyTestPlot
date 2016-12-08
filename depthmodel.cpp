#include "depthmodel.h"

DepthModel::DepthModel()
{

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
    return priceList.count(); //+grouped;
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
