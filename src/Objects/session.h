#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <vector>

#include "constantes.h"
#include "json/json.h"
#include "fonctions_json.h"
#include "fonctions.h"

#include "../ressources.h"

#include <QFile>
#include <QDir>

class Session
{
public:
    Session();
    Session(std::string file);
    Session(unsigned int id);
    Session(unsigned int id, std::string tulpa_name, int session_type_id, std::string description, int duration, std::string date);
    ~Session();

    void setFilePath(std::string path);
    void loadFromJSON();
    void save();

    std::string toString();

    /*Getters*/
    bool hasTulpa();
    std::string getFilePath();
    int getFullId();
    int getId();
    std::string getTulpaName();
    int getTypeId();
    std::string getType();
    std::string getDescription();
    std::string getDate();
    int getDuration();
    std::string getDurationString();
    std::string getWritingLog();

    /*Setters*/
    void setDescription(std::string desc);
    void setDuration(int t);
    void setID(unsigned int id);
    void setTypeID(unsigned int id);
    void setTulpaName(std::string name);
    void setDate(std::string date);
    void setWritingLog(std::string log);

private:
    unsigned int id;
    int session_type_id;
    std::string tulpa_name;
    std::string session_type;
    std::string description;
    std::string date;
    std::string writing_log;
    int duration;

    std::string local_file;

    Json::Value root;
};

#endif // SESSION_H
