#ifndef QCALENDARBOX_H
#define QCALENDARBOX_H

#include <QtWidgets>
#include "json/json.h"
#include "../ressources.h"

class QCalendarBox : public QDialog
{
public:
    QCalendarBox(QWidget *parent = 0);
    void setData(Json::Value root);
    QCalendarWidget *getCalendar();

private:
    QLabel *tulpa_name;
    QLabel *session_type;
    QLabel *time;
    QTextEdit* description;

    QCalendarWidget* calendar;
};

#endif // QCALENDARBOX_H
