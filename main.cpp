#include "main.h"

#include "mainwindow.h"
#include <QApplication>

#include "testplotpresenter.h"
#include "depthmodelpresenter.h"

BaseValues *baseValues_;

// **  https://habrahabr.ru/post/203254/
// ** #include "ThreadedObject.h"

// #include "main.moc"

void BaseValues::Construct()
{
    timeFormat=QLocale().timeFormat(QLocale::LongFormat).replace(" ","").replace("t","");
    dateTimeFormat=QLocale().dateFormat(QLocale::ShortFormat)+" "+timeFormat;

    groupPriceValue=0.0;
}


int main(int argc, char *argv[])
{
    bool res;
    baseValues_ = new BaseValues;
    // Первоначальная инициализация стуктуры данными
    baseValues.Construct();

    QApplication app(argc, argv);
    MainWindow *mainWin = new MainWindow();

    TestPlotPresenter *presenter = new TestPlotPresenter(mainWin);
    DepthModelPresenter *depthpresener = new DepthModelPresenter(mainWin);
    Q_UNUSED(presenter);
    Q_UNUSED(depthpresener);
    //mainWin.show();

    mainWin->show();

    // Нужно отправлять сигнал, о завершении работы программы, в наши дополнительны(й/е) поток(и)
    //res = QObject::connect (&app, SIGNAL (lastWindowClosed ()), &mainWin, SLOT (terminate ())); Q_ASSERT_X (res, "connect", "connection is not established");
    res = QObject::connect (&app, SIGNAL (lastWindowClosed ()), presenter, SLOT (gr_terminateSlot ())); Q_ASSERT_X (res, "connect", "connection is not established");

    return app.exec();
}
