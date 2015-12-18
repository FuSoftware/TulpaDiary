#include <QApplication>
#include <iostream>
#include <cstdlib>
#include <iomanip>

#include "mainwidget.h"
#include "constantes.h"
#include "Workers/qsessionfixer.h"

#include "Objects/sessionindex.h"
#include <QEventLoop>
#include <QDebug>

#include <QFile>

int main(int argc, char *argv[])
{
    std::freopen(LOG_FILE, "a", stdout);
    std::clog << endl;
    std::cout << std::endl;

    int exit_code;

    qDebug() << "Starting the software";
    QApplication a(argc, argv);

    if(!createMainDirs())
    {
        QMessageBox::critical(0,"Error",QString("Couldn't create the app directories. Please check the permissions at :\n") + QDir(DATA_FOLDER).absolutePath());
        exit(15);
    }


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
        w->setWindowTitle(QString(APP_NAME) + QString(" Debug ") + QString(VERSION));
    }
    else
    {
        w->setWindowTitle(QString(APP_NAME) + QString(" ") + QString(VERSION));
    }

    w->loadUI();
    //w.show();

    exit_code = a.exec();

    if(exit_code == EXIT_CODE_UPDATE)
    {
        //Updates the software
        QFile old_file(QString(EXECUTABLE));
        QFile new_file(QString(EXECUTABLE_DL));

        old_file.rename(QString(EXECUTABLE) + QString(".old"));
        new_file.rename(EXECUTABLE);
    }

    return exit_code;
}
