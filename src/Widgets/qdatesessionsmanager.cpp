#include "qdatesessionsmanager.h"

QDateSessionsManager::QDateSessionsManager(QDate date, QWidget *parent) : QWidget(parent)
{
    this->date = date;

    folder = QString(SESSION_FOLDER) + date.toString(DATE_TYPE) + QString("/");
    checkFolder(folder.toStdString());

    dir = new QDir(folder);
    dir->setFilter(QDir::Files|QDir::NoDotAndDotDot);

    loadSessions();

    mappers.push_back(new QSignalMapper(this));
    connect(mappers.at(EDIT), SIGNAL(mapped(int)), this, SLOT(editSession(int)));

    //mappers.push_back(new QSignalMapper(this));
    //connect(mappers.at(VIEW), SIGNAL(mapped(int)), this, SLOT(viewSession(int)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QLabel *label = new QLabel(tutorials[TUTO_SESSIONMANAGER],this);
    mainLayout->addWidget(label);

    pBA = new QPushButton("Add Session",this);
    n_files = dir->entryList().size();

    for(int i=0;i<n_files;i++)
    {
        QWidget *widget = loadSession(sessions.at(i),i);
        mainLayout->addWidget(widget);
    }

    QHBoxLayout *layoutAdd = new QHBoxLayout;
    layoutAdd->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
    layoutAdd->addWidget(pBA);
    layoutAdd->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
    mainLayout->addLayout(layoutAdd);

    setLayout(mainLayout);

    connect(pBA,SIGNAL(clicked()),this,SLOT(addSession()));
}

void QDateSessionsManager::loadSessions()
{
    delete dir;
    dir = new QDir(folder);
    dir->setFilter(QDir::Files|QDir::NoDotAndDotDot);

    sessions.clear();

    for(int i=0;i<dir->entryList().size();i++)
    {
        sessions.push_back(new Session(dir->entryInfoList().at(i).absoluteFilePath().toStdString()));
    }
}


QWidget *QDateSessionsManager::loadSession(Session *session, int i)
{
    QWidget *widget = new QWidget(this);

    QLabel *label = new QLabel(this);

    QHBoxLayout *layout = new QHBoxLayout;

    QString text = QString(session->toString().c_str());

    label->setText(text);

    layout->addWidget(label,15);

    /*
    QPushButton *pBV = new QPushButton("View",this);
    layout->addWidget(pBV);
    mappers.at(VIEW)->setMapping(pBV,i);
    connect(pBV, SIGNAL(clicked()), mappers.at(VIEW), SLOT(map()));
    */

    QPushButton *pBE = new QPushButton("Edit",this);
    layout->addWidget(pBE);
    mappers.at(EDIT)->setMapping(pBE,i);
    connect(pBE, SIGNAL(clicked()), mappers.at(EDIT), SLOT(map()));

    widget->setLayout(layout);

    return widget;
}

void QDateSessionsManager::editSession(int i)
{
    QEditSession *w = new QEditSession(sessions.at(i),true,0);
    w->show();
}

void QDateSessionsManager::addSession()
{
    Session *session = new Session();

    /*Create ID*/
    int id = n_files;

    while(sessionExists(date,id))
    {
        id++;
    }

    /*Loads the new session*/

    session->setID(id);
    session->setDate(date.toString(DATE_TYPE).toStdString());
    QEditSession *w = new QEditSession(session,true,0);
    w->show();
}
