#ifndef RESSOURCES
#define RESSOURCES

#include <QString>

#define OBJECT_NUMBER 6

enum Actions
{
    ACTION_ACTIVE_T =0,
    ACTION_ACTIVE_V,
    ACTION_ACTIVE_B,
    ACTION_PASSIVE,
    ACTION_MEDITATION,
    ACTION_END_LIST
};

const QString titles[OBJECT_NUMBER] = {"Session","Tulpa","Action type","Date","Time spent (Minutes)","Detailed description"};
const QString actions_string[ACTION_END_LIST] = {"Active Forcing (Talking)","Active Forcing (Visualisation)","Active Forcing (Both)","Passive Forcing","Meditation"};

#endif // RESSOURCES

