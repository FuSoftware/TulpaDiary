#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    startup_load();
}

void MainWidget::loadUI()
{
    outputInfo(L_DEBUG,"Loading main UI");

    w = new ScheduleWidget(this);
    t = new TulpaWidget(this);
    tab = new QTabWidget(this);
    guideList = new QGuideList(this);

    tab->addTab(w,"Schedule");
    tab->addTab(t,"Tulpas");
    tab->addTab(guideList,"Guides");

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(tab);

    setLayout(layout);

    outputInfo(L_DEBUG,"Main UI loaded");

    this->show();
    this->resize(0,0);
}

void MainWidget::startup_load()
{
    QThread *thread = new QThread;
    QStartupWorker *worker = new QStartupWorker(this);

    worker->moveToThread(thread);

    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}
