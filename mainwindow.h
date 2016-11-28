#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "charts/qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupPlot();
    ///
    /// \brief setupFinPlot - установки плоттера
    /// \param customPlot
    /// \details Утсановим данные для Фин-Графика
    ///
    void setupFinPlot(QCustomPlot *customPlot);
    void setupRealTimePlot(QCustomPlot *customPlot);
    void setupRealMyTimePlot(QCustomPlot *customPlot);

private slots:
  void realtimeDataSlot();
  void realtimeMyDataSlot();

private:
    Ui::MainWindow *ui;
    QString demoName;
    QTimer dataTimer;
    //int n = 500;
    QVector<double> volTime, volData; // (500);
    ///
    /// \brief lastPush - Последнее значение добавленное
    ///
    double lastPush;
    // А надо-ли нам его ?
    //QCPItemTracer *itemPlotPhaseTracer;
};

#endif // MAINWINDOW_H
