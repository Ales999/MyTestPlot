#include "depthmodelpresenter.h"
#include "itestplotview.h"

DepthModelPresenter::DepthModelPresenter( ITestPlotView *view, QObject *parent)
    : QObject(parent)
    //, depthAsksModel( new DepthModel(true)  )
    , depthBidsModel( new DepthModel(false) )
    , m_view( view )
{
    qDebug("Created DepthModelPresenter\n");


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
