#ifndef SESSIONINDEX_H
#define SESSIONINDEX_H

#include <iostream>
#include <QDate>
#include <QDebug>

#include "../fonctions.h"

class SessionIndex
{
public:
    SessionIndex(std::string str);
    SessionIndex(int id);
    SessionIndex(QDate date, int id);

    void loadFromString(std::string str);

    void setDate(QDate date);
    void setID(int id);
    QDate getDate();
    int getID();
    std::string getFileName();

private:
    QDate date;
    int id;
};

#endif // SESSIONINDEX_H
