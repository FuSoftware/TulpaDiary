#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include "constantes.h"
#include "qdatesessionsmanager.h"

#include <QtWidgets>
#include <QCalendarWidget>

class ScheduleWidget : public QWidget
{
    Q_OBJECT
public:
    ScheduleWidget(QWidget *parent = 0);

signals:

public slots:
    void on_date_clicked(QDate date);

private:
    QCalendarWidget *calendar;
};

#endif // SCHEDULEWIDGET_H
