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

enum GuideType
{
    G_GENERAL =0,
    G_PERSONALITY,
    G_SENTIENCE,
    G_VISUALIZATION,
    G_CONCENTRATION,
    G_VOCALIZATION,
    G_FORCING,
    G_MOTIVATION,
    G_IMPOSITION,
    G_POSSESSION,
    G_OTHER,
    G_END_LIST
};

const QString titles[OBJECT_NUMBER] = {"Session","Tulpa","Action type","Date","Time spent (Minutes)","Detailed description"};
const QString actions_string[ACTION_END_LIST] = {"Active Forcing (Talking)","Active Forcing (Visualisation)","Active Forcing (Both)","Passive Forcing","Meditation"};

const QString guide_types[G_END_LIST] = {"GENERAL","PERSONALITY","SENTIENCE","VISUALIZATION","CONCENTRATION","VOCALIZATION","FORCING","MOTIVATION","IMPOSITION","POSSESSION","OTHER"};

/*Tutorial labels*/
enum Tutorials{
    TUTO_CALENDAR = 0,
    TUTO_SESSIONMANAGER,
    TUTO_EDITSESSION,
    TUTO_END_LIST
};

const QString tutorials[TUTO_END_LIST]= {"To edit a date's sessions, open the date by double-clicking it",
                                         "Here are listed all the sessions affected to the current date.\nPlease note that for now, you'll have to re-open the date to refresh the sessions list.\nThey are not automatically refreshed",
                                         ""};

#endif // RESSOURCES

