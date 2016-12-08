#ifndef DEPTHMODEL_H
#define DEPTHMODEL_H

#include <QAbstractItemModel>
#include <QStringList>
#include "depthitem.h"

class DepthModel : public QAbstractItemModel
{
public:
    DepthModel(bool isAskData=true);

    // Impl from QAbstractItemModel
    QModelIndex index(int row, int column, const QModelIndex &parent=QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    // End Impl

    void setAsk(bool on);

    // Обновляем ордера
    void depthUpdateOrders(QList<DepthItem> *items);

private:
    bool isAsk;
    int columnsCount;
    bool originalIsAsk;
    bool somethingChanged;

    QList<double> priceList;
    QList<double> volumeList;
    QList<double> sizeList;
    QList<double> sizePriceList;
    QList<int> directionList;

    // Обновляем ордер
    void depthUpdateOrder(DepthItem item);
    void sizeListRemoveAt(int);
    double &sizeListAt(int);


};

#endif // DEPTHMODEL_H
