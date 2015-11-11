#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <vector>

#include "constantes.h"
#include "json/json.h"
#include "fonctions_json.h"
#include "fonctions.h"

class Session
{
public:
    Session();
    Session(int id);
    Session(int id, std::string tulpa_name, std::string session_type, std::string description, int duration, int time);
    ~Session();

    void loadFromJSON();

    int getId();
    std::string getTulpaName();
    std::string getType();
    std::string getDescription();
    int getTime();
    int getDuration();

private:
    int id;
    std::string tulpa_name;
    std::string session_type;
    std::string description;
    int time;
    int duration;

    std::string local_file;

    Json::Value root;
};

#endif // SESSION_H