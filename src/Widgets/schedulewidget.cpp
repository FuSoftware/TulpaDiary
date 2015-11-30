#include "schedulewidget.h"

ScheduleWidget::ScheduleWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *labelTutorial = new QLabel(tutorials[TUTO_CALENDAR],this);
    calendar = new QCalendarWidget(this);

    layout->addWidget(labelTutorial);
    layout->addWidget(calendar);

    setLayout(layout);

    connect(calendar,SIGNAL(activated(QDate)),this,SLOT(on_date_clicked(QDate)));

    resize(0,0);
}


void ScheduleWidget::on_date_clicked(QDate date)
{
    QDateSessionsManager *widget = new QDateSessionsManager(date,0);
    widget->setWindowTitle(date.toString("d MMMM yyyy"));
    widget->show();
}
