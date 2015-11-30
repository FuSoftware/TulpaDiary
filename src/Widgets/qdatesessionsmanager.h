#ifndef QDATESESSIONSMANAGER_H
#define QDATESESSIONSMANAGER_H

#include <QtWidgets>

#include "../Objects/session.h"

#include "qeditsession.h"

enum Mappers{
    EDIT = 0,
    DEL
};

class QDateSessionsManager : public QWidget
{
    Q_OBJECT
public:
    QDateSessionsManager(QDate date, QWidget *parent = 0);
    void loadSessionFiles();
    QWidget *loadSession(Session *session, unsigned int i);

    void clearSessionsUI();

signals:

public slots:
    void loadUI();
    void editSession(unsigned int i);
    void deleteSession(unsigned int i);
    void addSession();

private:
    QDate date;
    int n_files;

    QDir *dir;
    QString folder;
    QList<QSignalMapper*> mappers;

    QPushButton *pBA;
    QLabel *label;

    std::vector<Session*> sessions;

    QList<QWidget*> childWidgets;
};

#endif // QDATESESSIONSMANAGER_H
