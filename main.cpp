#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("qqqqqq");
    Widget w;
    w.resize(1920,1080);
    w.show();
    return a.exec();
}
