#ifndef QSTARTUPWORKER_H
#define QSTARTUPWORKER_H

#include <QtWidgets>

#include "../fonctions.h"

class QStartupWorker : public QObject
{
    Q_OBJECT
public:
    QStartupWorker(QObject *parent = 0);
    int main_routine();

signals:
    void finished();

public slots:
    void process();

};

#endif // QSTARTUPWORKER_H
