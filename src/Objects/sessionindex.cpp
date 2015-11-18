#include "sessionindex.h"

/*
Example date : 17 Nov 2015 - ID = 1
Full ID = 201511171
Date ID = 20151117
Sess ID = 1
*/

SessionIndex::SessionIndex(std::string str)
{
    loadFromString(str);
}

SessionIndex::SessionIndex(int id)
{
    std::string str = intToString(id);
    int i = 0;
    loadFromString(str);
}

void SessionIndex::loadFromString(std::string str)
{
    std::string str_date = str.substr(0,8);
    std::string str_id = str.substr(8,str.size()-7);

    int y,m,d;

    std::string str_y,str_m,str_d;
    str_y = str_date.substr(0,4);
    str_m = str_date.substr(4,2);
    str_d = str_date.substr(6,2);

    y = atoi(str_y.c_str());
    m = atoi(str_m.c_str());
    d = atoi(str_d.c_str());

    this->date.setDate(y,m,d);
    this->id = atoi(str_id.c_str());
}

SessionIndex::SessionIndex(QDate date, int id)
{
    this->date = date;
    this->id = id;
}

void SessionIndex::setDate(QDate date)
{
    this->date = date;
}

void SessionIndex::setID(int id)
{
    this->id = id;
}

QDate SessionIndex::getDate()
{
    return this->date;
}

int SessionIndex::getID()
{
    return this->id;
}

std::string SessionIndex::getFileName()
{
    QString file = QString(SESSION_FOLDER) + date.toString(DATE_TYPE) + QString("/") + QString::number(id) + QString(".json");
    return file.toStdString();
}

