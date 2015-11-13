#include "widget.h"
#include <QApplication>

#include "Widgets/qguidelist.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    if(DEBUG)
    {
        w.setWindowTitle(QString(APP_NAME) + QString(" ") + QString(VERSION));
    }
    else
    {
        w.setWindowTitle(QString(APP_NAME) + QString(" Debug ") + QString(VERSION));
    }
    w.show();

    return a.exec();
}
