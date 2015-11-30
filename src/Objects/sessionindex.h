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
    SessionIndex(unsigned int id);
    SessionIndex(QDate date, unsigned int id);

    void loadFromString(std::string str);

    void setDate(QDate date);
    void setID(unsigned int id);
    QDate getDate();
    int getID();
    std::string getFileName();

private:
    QDate date;
    unsigned int id;
};

#endif // SESSIONINDEX_H
