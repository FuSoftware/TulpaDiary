#include "widget.h"
#include <QApplication>

#include "Widgets/schedulewidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    //ScheduleWidget w;

    w.setWindowTitle(QString(APP_NAME) + QString(" ") + QString(VERSION));
    w.show();

    return a.exec();
}
