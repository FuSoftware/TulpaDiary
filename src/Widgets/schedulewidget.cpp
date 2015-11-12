#include "schedulewidget.h"

ScheduleWidget::ScheduleWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;

    calendar = new QCalendarWidget(this);

    layout->addWidget(calendar);

    setLayout(layout);
}

