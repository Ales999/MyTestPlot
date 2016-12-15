#ifndef DEPTHMODEL_H
#define DEPTHMODEL_H

#include <QAbstractItemModel>
#include <QStringList>
#include "depthitem.h"
#include "main.h"

///
/// \brief The DepthModel class
/// Общий класс модели для Ask и Bid (для каждого свой объект будет)
///
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

    void reloadVisibleItems();
    void setAsk(bool on);
    void calculateSize();

    // Обновляем ордера
    void depthUpdateOrders(QList<DepthItem> *items);

private:
    bool isAsk;
    int columnsCount;
    bool originalIsAsk;
    bool somethingChanged;

    // For test
    QVector<QVector<int> > dataset;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    // End test

    QList<double> priceList;
    QList<double> volumeList;
    QList<double> sizeList;
    QList<double> sizePriceList;
    QList<int> directionList;

    double groupedPrice;
    double groupedVolume;

    // Обновляем ордер
    void depthUpdateOrder(DepthItem item);
    void sizeListRemoveAt(int);
    double &sizeListAt(int);

private slots:
    void delayedReloadVisibleItems();

};

#endif // DEPTHMODEL_H
