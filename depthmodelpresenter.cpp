#include "depthmodelpresenter.h"
#include "itestplotview.h"

DepthModelPresenter::DepthModelPresenter( ITestPlotView *view, QObject *parent)
    : QObject(parent)
    //, depthAsksModel( new DepthModel(true)  )
    , depthBidsModel( new DepthModel(false) )
    , m_view( view )
{
    qDebug("Created DepthModelPresenter\n");
    // Test add data
    QList<DepthItem> *items = new QList<DepthItem>();
    DepthItem item1, item2;
    item1.price = 12.0;
    item1.volume = 0.5;
    item2.price = 14.4;
    item2.volume = 1.8;

    if (item1.isValid())
        items->append(item1);//  () << item1;
    if(item2.isValid())
        items->append(item2);

    depthBidsModel->depthUpdateOrders(items);
    // End test add data

//    depthAsksModel->isAsk = true;
//    depthBidsModel->isAsk = false;

//    depthBidsModel->setHeaderData(0, Qt::Horizontal, tr("MyTest"));
//    depthBidsModel->setHeaderData(1, Qt::Horizontal, tr("Volume"));
//    depthBidsModel->setHorizontalHeaderItem
//    emit depthBidsModel->headerDataChanged(Qt::Horizontal, 0, 1);
    view->setBidTable(depthBidsModel);


/*
    // test insert
     QList<DepthItem> *tstAsk = new QList<DepthItem>();
     DepthItem item1; item1.price = 100.0; item1.volume= 4 ; tstAsk->insert(1, item1);

     depthAsksModel->depthUpdateOrders(tstAsk);
     depthAsksModel->reloadVisibleItems();
*/
    // For test
     model = new QStandardItemModel(8, 2, this);
     model->setHeaderData(0, Qt::Horizontal, tr("Label"));
     model->setHeaderData(1, Qt::Horizontal, tr("Quantity"));

     view->setAskTable(model);


}
