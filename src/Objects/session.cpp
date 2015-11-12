#include "session.h"

Session::Session()
{

}

Session::Session(int id)
{
    local_file = std::string(SESSION_FOLDER) + intToString(id) + std::string(".json");

    checkFolder(getFolder(local_file));

    if(checkFile(local_file))
    {
        root = loadJSONFile(local_file.c_str());

        loadFromJSON();
    }
    else
    {
        outputInfo(L_ERROR,std::string("Session ") + intToString(id) + std::string(" doesn't exist"));
    }
}

Session::Session(int id, std::string tulpa_name, std::string session_type, int session_type_id, std::string description, int duration, std::string time)
{
    local_file = std::string(SESSION_FOLDER) + intToString(id) + std::string(".json");

    root["id"] = id;
    root["id_action"] = session_type_id;
    root["tulpa_name"] = tulpa_name;
    root["session_type"] = session_type;
    root["description"] = description;
    root["time"] = time;
    root["duration"] = duration;
    saveJSONFile(root,local_file.c_str());

    loadFromJSON();
}

Session::~Session()
{

}

void Session::loadFromJSON()
{
    this->id = root["id"].asInt();
    this->session_type_id = root["id_action"].asInt();
    tulpa_name = root["tulpa_name"].asString();
    session_type = root["session_type"].asString();
    description = root["description"].asString();
    time = root["time"].asString();
    duration = root["duration"].asInt();
}

int Session::getId()
{
    return id;
}
std::string Session::getTulpaName()
{
    return tulpa_name;
}
int Session::getTypeId()
{
    return this->session_type_id;
}

std::string Session::getType()
{
    return session_type;
}
std::string Session::getDescription()
{
    return description;
}
std::string Session::getTime()
{
    return time;
}
int Session::getDuration()
{
    return duration;
}


