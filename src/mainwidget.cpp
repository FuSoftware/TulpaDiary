#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{

}

void MainWidget::loadUI()
{
    outputInfo(L_DEBUG,"Loading main UI");

    w = new ScheduleWidget(this);
    t = new TulpaWidget(this);
    tab = new QTabWidget(this);

    tab->addTab(w,"Schedule");
    tab->addTab(t,"Tulpas");

    QVBoxLayout *layout = new QVBoxLayout;

    layout->addWidget(tab);

    setLayout(layout);

    outputInfo(L_DEBUG,"Main UI loaded");

    this->show();
}

