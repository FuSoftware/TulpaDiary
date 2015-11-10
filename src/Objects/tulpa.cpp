#include "tulpa.h"

Tulpa::Tulpa()
{

}

Tulpa::Tulpa(std::string name)
{
    loadByName(name);
}

Tulpa::~Tulpa()
{

}

void Tulpa::loadByName(std::string name)
{
    this->name = name;
    local_file = std::string(TULPA_FOLDER) + this->name + std::string(".json");
    checkFolder(getFolder(local_file));

    this->name[0] = toupper(this->name[0]);

    int i=0;

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

    i=0;
    while(root["session_id"][i] != Json::nullValue)
    {
        loadSession(root["session_id"][i].asInt());
        i++;
    }

    birth_time = root["birth_time"].asInt();
    first_word_time = root["first_word_time"].asInt();
}

void Tulpa::save()
{
    root["personality_traits"];
    root["name"] = this->name;
    root["birth_time"] = birth_time;
    root["first_word_time"] = first_word_time;

    saveJSONFile(root,local_file.c_str());
}

void Tulpa::addPersonalityTrait(std::string trait)
{
    personality_traits.push_back(trait);
}

void Tulpa::addSessions(Session session)
{
    sessions.push_back(session);
    sessions_id.push_back(session.getId());
}

void Tulpa::loadSession(int id)
{
    Session session(id);
    sessions.push_back(session);
    sessions_id.push_back(session.getId());
}

void Tulpa::setName(std::string name)
{
    this->name = name;
}

void Tulpa::setBirthTime(int time)
{
    birth_time = time;
}
void Tulpa::setFirstWordTime(int time)
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

std::string Tulpa::getPersonalityTrait(int i)
{
    return personality_traits[i];
}
std::vector<std::string> Tulpa::getPersonalityTraits()
{
    return personality_traits;
}

int Tulpa::getBirthTime()
{
    return birth_time;
}
int Tulpa::getFirstWordTime()
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
