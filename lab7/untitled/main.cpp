#include <QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    Widget w;
    //w.showFullScreen();
    w.show();

    return a.exec();
}
