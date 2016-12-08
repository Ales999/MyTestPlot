#ifndef DEPTHMODELPRESENTER_H
#define DEPTHMODELPRESENTER_H

#include <QObject>

#include "depthmodel.h"
#include "itestplotview.h"

class DepthModelPresenter : public QObject
{
    Q_OBJECT
public:
    explicit DepthModelPresenter(ITestPlotView *view, QObject *parent = 0);

private:

    DepthModel      *d_model;
    ITestPlotView   *m_view;



signals:

public slots:
};

#endif // DEPTHMODELPRESENTER_H
