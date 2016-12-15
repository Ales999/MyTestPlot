#ifndef DEPTHMODELPRESENTER_H
#define DEPTHMODELPRESENTER_H

#include <QObject>

#include "depthmodel.h"
#include "itestplotview.h"

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
QT_END_NAMESPACE

class DepthModelPresenter : public QObject
{
    Q_OBJECT
public:
    explicit DepthModelPresenter(ITestPlotView *view, QObject *parent = 0);

private:

    //DepthModel      *d_model;
    DepthModel      *depthAsksModel;
    DepthModel      *depthBidsModel;
    // TODO: next
    //TradesModel *tradesModel;
    //HistoryModel *historyModel;

    ITestPlotView   *m_view;

    // for test
   QAbstractItemModel *model;

signals:

public slots:
};

#endif // DEPTHMODELPRESENTER_H
