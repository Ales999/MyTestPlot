#include "mainwindow.h"
#include <QApplication>

// **  https://habrahabr.ru/post/203254/
// ** #include "ThreadedObject.h"

// #include "main.moc"

int main(int argc, char *argv[])
{
    bool res;
    //int strtmt;
    QApplication app(argc, argv);
    MainWindow mainWin;
    mainWin.show();
    // Нужно отправлять сигнал, о завершении работы программы, в наши дополнительны(й/е) поток(и)
    res = QObject::connect (&app, SIGNAL (lastWindowClosed ()), &mainWin, SLOT (terminate ())); Q_ASSERT_X (res, "connect", "connection is not established");
    return app.exec();
}
