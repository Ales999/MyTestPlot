#include "mainwindow.h"
#include <QApplication>

#include "testplotpresenter.h"
#include "depthmodelpresenter.h"

// **  https://habrahabr.ru/post/203254/
// ** #include "ThreadedObject.h"

// #include "main.moc"

int main(int argc, char *argv[])
{
    bool res;
    //int strtmt;
    QApplication app(argc, argv);
    //MainWindow mainWin;

    MainWindow *mainWin = new MainWindow();

    TestPlotPresenter *presenter = new TestPlotPresenter(mainWin);
    Q_UNUSED(presenter);
    //mainWin.show();

    mainWin->show();

    // Нужно отправлять сигнал, о завершении работы программы, в наши дополнительны(й/е) поток(и)
    //res = QObject::connect (&app, SIGNAL (lastWindowClosed ()), &mainWin, SLOT (terminate ())); Q_ASSERT_X (res, "connect", "connection is not established");
    res = QObject::connect (&app, SIGNAL (lastWindowClosed ()), presenter, SLOT (gr_terminateSlot ())); Q_ASSERT_X (res, "connect", "connection is not established");

    return app.exec();
}
