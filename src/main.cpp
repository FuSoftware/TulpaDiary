#include <QApplication>
#include <iostream>
#include <cstdlib>
#include <iomanip>

#include "mainwidget.h"
#include "Workers/qsessionfixer.h"

#include "Objects/sessionindex.h"
#include <QEventLoop>
#include <QDebug>

int main(int argc, char *argv[])
{

    std::freopen(LOG_FILE, "a", stdout);

    std::clog << endl;

    std::cout << std::endl;


    QApplication a(argc, argv);


    QSessionFixer *f;
    f = new QSessionFixer(0);

    f->fix();

    /*This is temporary*/
    QEventLoop loop;
    QTimer::singleShot(500, &loop, SLOT(quit()));
    loop.exec();


    MainWidget *w;
    w = new MainWidget(0);

    if(DEBUG)
    {
        w->setWindowTitle(QString(APP_NAME) + QString(" ") + QString(VERSION));
    }
    else
    {
        w->setWindowTitle(QString(APP_NAME) + QString(" Debug ") + QString(VERSION));
    }

    w->loadUI();
    //w.show();

    return a.exec();
}
