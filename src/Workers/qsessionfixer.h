/*QSessionFixer
 *
 * This class fixes, on startup, the session and tulpa files
 * It ensures that they are properly located, and updates them from one version to another.
 */

#ifndef QSESSIONFIXER_H
#define QSESSIONFIXER_H

#include <QtWidgets>

#include "../constantes.h"
#include "../fonctions_json.h"
#include "../fonctions.h"

#include "../Widgets/qcalendarbox.h"

#include "../Objects/sessionindex.h"
#include "../Objects/session.h"
#include "../Objects/tulpa.h"

class QSessionFixer : public QWidget
{
    Q_OBJECT
public:
    QSessionFixer(QWidget *parent = 0);
    void fix();
    bool isFinished();
    void terminate();
    void fixSessionIds();
    void fixID(Session* session, QString folder_id);

signals:
    void finished();

public slots:
    void loadLostSession(QString path);
    void fixLostSession(QDate date);

private:
    QDir *dir;
    Json::Value root;
    QCalendarBox *calendar;
    QString json_path;

    SessionIndex *session_index;
    unsigned int index;
    unsigned int index_max;
    bool f;
};

#endif // QSESSIONFIXER_H
