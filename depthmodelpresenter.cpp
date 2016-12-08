#include "depthmodelpresenter.h"
#include "itestplotview.h"

DepthModelPresenter::DepthModelPresenter( ITestPlotView *view, QObject *parent)
    : QObject(parent)
    , d_model( new DepthModel() )
    , m_view( view )
{
    qDebug("Created DepthModelPresenter\n");
}
