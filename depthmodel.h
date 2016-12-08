#ifndef DEPTHMODEL_H
#define DEPTHMODEL_H

#include <QAbstractItemModel>
#include <QStringList>
#include "depthitem.h"

class DepthModel : public QAbstractItemModel
{
public:
    DepthModel();

    // Impl from QAbstractItemModel
    QModelIndex index(int row, int column, const QModelIndex &parent=QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    // End Impl

private:
    int columnsCount;
    QList<double> priceList;

};

#endif // DEPTHMODEL_H
