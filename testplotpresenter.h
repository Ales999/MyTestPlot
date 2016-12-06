#ifndef TESTPLOTPRESENTER_H
#define TESTPLOTPRESENTER_H

#include <QObject>
#include "testplotmodel.h"

class ITestPlotView;

class TestPlotPresenter : public QObject
{
    Q_OBJECT
public:
    explicit TestPlotPresenter(QObject *parent = 0);

private:
    void refreshView() const;

    TestPlotModel *m_model;
    ITestPlotView *m_view;

signals:

public slots:

private slots:

};

#endif // TESTPLOTPRESENTER_H
