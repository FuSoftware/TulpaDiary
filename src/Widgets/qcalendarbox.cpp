#include "qcalendarbox.h"

QCalendarBox::QCalendarBox(QWidget *parent) : QDialog(parent)
{
    tulpa_name = new QLabel(this);
    session_type = new QLabel(this);
    time = new QLabel(this);
    description = new QTextEdit(this);
    calendar = new QCalendarWidget(this);

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(tulpa_name);
    layout->addWidget(session_type);
    layout->addWidget(time);
    layout->addWidget(description);
    layout->addWidget(calendar);

    setLayout(layout);
}

void QCalendarBox::setData(Json::Value root)
{
    tulpa_name->setText(root["tulpa_name"].asCString());
    session_type->setText(actions_string[root["id_action"].asInt()]);
    time->setText(root["time"].asCString());
    description->setText(root["description"].asCString());
}

QCalendarWidget* QCalendarBox::getCalendar()
{
    return this->calendar;
}

