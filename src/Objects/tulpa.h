#ifndef TULPA_H
#define TULPA_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "constantes.h"
#include "json/json.h"
#include "fonctions_json.h"
#include "fonctions.h"

#include "session.h"

#include "sessionindex.h"

class Tulpa
{
public:
    Tulpa();
    Tulpa(std::string name, bool load_sessions = true);
    ~Tulpa();

    void loadByName(std::string name, bool load_sessions = true);
    void save();
    void generateFilePath();
    void addPersonalityTrait(std::string trait);
    void clearSessions();
    void addSessions(Session session);

    void loadSession(unsigned int id);

    void setName(std::string name);
    void setBirthTime(std::string time);
    void setFirstWordTime(std::string time);
    void setPersonalityTraits(std::vector<std::string> traits);

    std::string getPersonalityTrait(unsigned int i);
    std::vector<std::string> getPersonalityTraits();
    std::string getName();
    std::string getBirthTime();
    std::string getFirstWordTime();
    std::vector<Session> getSessions();
    std::vector<int> getSessionsIds();

private:
    Json::Value root;

    std::string name;

    std::string birth_time;
    std::string first_word_time;

    std::vector<std::string> personality_traits;
    std::vector<Session> sessions;
    std::vector<int> sessions_id;

    bool has_picture;
    std::string picture_path;

    std::string local_file;
};

#endif // TULPA_H
