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

SessionIndex::SessionIndex(unsigned int id)
{
    std::string str = intToString(id);
    loadFromString(str);
}

void SessionIndex::loadFromString(std::string str)
{
    std::string str_id = str.substr(8,str.size()-7);

    this->date = dateFromString(str);
    this->id = atoi(str_id.c_str());
}

SessionIndex::SessionIndex(QDate date, unsigned int id)
{
    this->date = date;
    this->id = id;
}

void SessionIndex::setDate(QDate date)
{
    this->date = date;
}

void SessionIndex::setID(unsigned int id)
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

