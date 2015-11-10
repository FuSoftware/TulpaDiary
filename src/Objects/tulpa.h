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

class Tulpa
{
public:
    Tulpa();
    Tulpa(std::string name);
    ~Tulpa();

    void loadByName(std::string name);
    void save();

    void addPersonalityTrait(std::string trait);
    void addSessions(Session session);

    void loadSession(int id);

    void setName(std::string name);
    void setBirthTime(int time);
    void setFirstWordTime(int time);
    void setPersonalityTraits(std::vector<std::string> traits);

    std::string getPersonalityTrait(int i);
    std::vector<std::string> getPersonalityTraits();
    std::string getName();
    int getBirthTime();
    int getFirstWordTime();
    std::vector<Session> getSessions();
    std::vector<int> getSessionsIds();

private:
    Json::Value root;

    std::string name;

    int birth_time;
    int first_word_time;

    std::vector<std::string> personality_traits;
    std::vector<Session> sessions;
    std::vector<int> sessions_id;

    bool has_picture;
    std::string picture_path;

    std::string local_file;
};

#endif // TULPA_H
