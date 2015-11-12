#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include <QtWidgets>
#include <QCalendarWidget>

class ScheduleWidget : public QWidget
{
    Q_OBJECT
public:
    ScheduleWidget(QWidget *parent = 0);

signals:

public slots:

private:
    QCalendarWidget * calendar;
};

#endif // SCHEDULEWIDGET_H
