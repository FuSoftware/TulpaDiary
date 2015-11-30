#include "tulpa.h"

Tulpa::Tulpa()
{

}

Tulpa::Tulpa(std::string name, bool load_sessions)
{
    loadByName(name, load_sessions);
}

Tulpa::~Tulpa()
{

}

void Tulpa::loadByName(std::string name, bool load_sessions)
{
    this->name = name;
    local_file = std::string(TULPA_FOLDER) + this->name + std::string(".json");
    checkFolder(getFolder(local_file));

    this->name[0] = toupper(this->name[0]);

    unsigned int i=0;

    if(!checkFile(local_file))
    {
        root["personality_traits"] = Json::arrayValue;
        root["name"] = this->name;
        root["birth_time"] = (int)time(NULL);
        root["first_word_time"] = 0;

        saveJSONFile(root,local_file.c_str());
    }

    root = loadJSONFile(local_file.c_str());

    personality_traits.clear();

    while(root["personality_traits"][i] != Json::nullValue)
    {
        addPersonalityTrait(root["personality_traits"][i].asString());
        i++;
    }

    if(load_sessions)
    {
        i=0;
        while(root["session_id"][i] != Json::nullValue)
        {
            loadSession(root["session_id"][i].asInt());
            i++;
        }
    }

    birth_time = root["birth_time"].asString();
    first_word_time = root["first_word_time"].asString();
}

void Tulpa::save()
{
    Json::Value root;

    for(unsigned int i=0;i<personality_traits.size();i++)
    {
        root["personality_traits"][i] = personality_traits.at(i);
    }

    for(unsigned int i=0;i<sessions_id.size();i++)
    {
        root["session_id"][i] = sessions_id.at(i);
    }

    root["name"] = this->name;
    root["birth_time"] = birth_time;
    root["first_word_time"] = first_word_time;

    saveJSONFile(root,local_file.c_str());
}

void Tulpa::generateFilePath()
{
    this->local_file = std::string(TULPA_FOLDER) + this->name + std::string(".json");
}

void Tulpa::addPersonalityTrait(std::string trait)
{
    personality_traits.push_back(trait);
}

void Tulpa::clearSessions()
{
    sessions.clear();
}

void Tulpa::addSessions(Session session)
{
    sessions.push_back(session);
    sessions_id.push_back(session.getFullId());
}

void Tulpa::loadSession(unsigned int id)
{   
    SessionIndex index(id);
    //qDebug() << "Loading session" << id << "for" << name.c_str() << ":" << index.getFileName().c_str();

    Session session(index.getFileName());
    addSessions(session);
}

void Tulpa::setName(std::string name)
{
    this->name = name;
}

void Tulpa::setBirthTime(std::string time)
{
    birth_time = time;
}
void Tulpa::setFirstWordTime(std::string time)
{
    first_word_time = time;
}

void Tulpa::setPersonalityTraits(std::vector<std::string> traits)
{
    this->personality_traits = traits;
}

std::string Tulpa::getName()
{
    return this->name;
}

std::string Tulpa::getPersonalityTrait(unsigned int i)
{
    return personality_traits[i];
}
std::vector<std::string> Tulpa::getPersonalityTraits()
{
    return personality_traits;
}

std::string Tulpa::getBirthTime()
{
    return birth_time;
}
std::string Tulpa::getFirstWordTime()
{
    return first_word_time;
}

std::vector<Session> Tulpa::getSessions()
{
    return sessions;
}

std::vector<int> Tulpa::getSessionsIds()
{
    return sessions_id;
}
