#include "session.h"

Session::Session() : Session(0, "", 0, "", 0,"")
{

}

Session::Session(std::string file)
{
    local_file = file;

    QFileInfo q_file(local_file.c_str());
    std::string date = q_file.absoluteDir().dirName().toStdString();

    root = loadJSONFile(local_file.c_str());
    loadFromJSON();

    setDate(date);
}

/*
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
*/

Session::Session(int id, std::string tulpa_name, int session_type_id, std::string description, int duration, std::string date)
{
    setID(id);
    setTypeID(session_type_id);
    setTulpaName(tulpa_name);
    setDescription(description);
    setDuration(duration);
    setDate(date);
}


Session::~Session()
{

}

void  Session::setFilePath(std::string path)
{
    this->local_file = path;
}


void Session::loadFromJSON()
{
    setID(root["id"].asInt());
    setTypeID(root["id_action"].asInt());
    setTulpaName(root["tulpa_name"].asString());
    setDescription(root["description"].asString());
    setDuration(root["duration"].asInt());
    setDate(root["date"].asString());
}

void Session::save()
{
    if(local_file.empty())
    {
       this->local_file = std::string(SESSION_FOLDER) + date + std::string("/") + intToString(id) + std::string(".json");
    }

    Json::Value root;

    root["id"] = getId();
    root["id_action"] = getTypeId();
    root["tulpa_name"] = getTulpaName();
    root["description"] = getDescription();
    root["duration"] = getDuration();
    root["date"] = date;

    saveJSONFile(root,local_file.c_str());
}

std::string Session::toString()
{
    std::string string;

    string = intToString(this->getId()) + " - " + this->getTulpaName() + " - " + this->getType() + " - " + this->getDurationString();

    return string;
}

bool Session::hasTulpa()
{
    if(getTulpaName().compare("No Tulpa") == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

std::string Session::getFilePath()
{
    return this->local_file;
}

int Session::getFullId()
{
    std::string str = this->date + intToString(id);
    return atoi(str.c_str());
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
std::string Session::getDate()
{
    return this->date;
}

int Session::getDuration()
{
    return duration;
}
std::string Session::getDurationString()
{
    int t = duration;
    int d,h,m;
    std::string str = "";

    /*Days*/
    if(t > 1440)
    {
        d = t/1440;
        t %= 1440;
        str += intToString(d);
        str += std::string(" days ");
    }

    /*Hours*/
    if(t > 60)
    {
        h = t/60;
        t %= 60;
        str += intToString(h);
        str += std::string(" hours ");
    }

    /*Minutes*/
    if(t > 0)
    {
        m = t;
        str += intToString(m);
        str += std::string(" minutes");
    }


    return str;
}


void Session::setDescription(std::string desc)
{
    this->description = desc;
}

void Session::setDuration(int t)
{
    this->duration = t;
}

void Session::setID(int id)
{
    this->id = id;
}

void Session::setTypeID(int id)
{
    this->session_type_id = id;
    this->session_type = actions_string[id].toStdString();
}

void Session::setTulpaName(std::string name)
{
    this->tulpa_name = name;
}

void Session::setDate(std::string date)
{
    this->date = date;
}
