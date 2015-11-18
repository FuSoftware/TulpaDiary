#ifndef QDATESESSIONSMANAGER_H
#define QDATESESSIONSMANAGER_H

#include <QtWidgets>

#include "../Objects/session.h"

#include "qeditsession.h"

enum Mappers{
    EDIT = 0,
    VIEW
};

class QDateSessionsManager : public QWidget
{
    Q_OBJECT
public:
    QDateSessionsManager(QDate date, QWidget *parent = 0);
    void loadSessions();
    QWidget *loadSession(Session *session, int i);

signals:

public slots:
    void editSession(int i);
    void addSession();

private:
    QDate date;
    int n_files;

    QDir *dir;
    QString folder;
    QList<QSignalMapper*> mappers;

    QPushButton *pBA;

    std::vector<Session*> sessions;
};

#endif // QDATESESSIONSMANAGER_H
