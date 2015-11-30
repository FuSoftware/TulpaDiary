#include "qdatesessionsmanager.h"

QDateSessionsManager::QDateSessionsManager(QDate date, QWidget *parent) : QWidget(parent)
{
    this->date = date;

    folder = QString(SESSION_FOLDER) + date.toString(DATE_TYPE) + QString("/");
    checkFolder(folder.toStdString());

    dir = new QDir(folder);
    dir->setFilter(QDir::Files|QDir::NoDotAndDotDot);

    mappers.push_back(new QSignalMapper(this));
    connect(mappers.at(EDIT), SIGNAL(mapped(int)), this, SLOT(editSession(int)));

    mappers.push_back(new QSignalMapper(this));
    connect(mappers.at(DEL), SIGNAL(mapped(int)), this, SLOT(deleteSession(int)));

    pBA = new QPushButton("Add Session",this);
    label = new QLabel(tutorials[TUTO_SESSIONMANAGER],this);

    connect(pBA,SIGNAL(clicked()),this,SLOT(addSession()));

    loadUI();
}

void QDateSessionsManager::loadUI()
{
    clearSessionsUI();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(label);

    loadSessionFiles();

    n_files = dir->entryList().size();

    for(int i=0;i<n_files;i++)
    {
        QWidget *widget = loadSession(sessions.at(i),i);
        mainLayout->addWidget(widget);
        childWidgets.push_back(widget);
    }

    QHBoxLayout *layoutAdd = new QHBoxLayout;
    layoutAdd->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
    layoutAdd->addWidget(pBA);
    layoutAdd->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
    mainLayout->addLayout(layoutAdd);

    setLayout(mainLayout);
}

void QDateSessionsManager::loadSessionFiles()
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


QWidget *QDateSessionsManager::loadSession(Session *session, unsigned int i)
{
    QWidget *widget = new QWidget(this);

    QLabel *label = new QLabel(this);

    QHBoxLayout *layout = new QHBoxLayout;

    QString text = QString(session->toString().c_str());

    label->setText(text);

    layout->addWidget(label,15);

    QPushButton *pBE = new QPushButton("Edit",this);
    layout->addWidget(pBE);
    mappers.at(EDIT)->setMapping(pBE,i);
    connect(pBE, SIGNAL(clicked()), mappers.at(EDIT), SLOT(map()));

    QPushButton *pBD = new QPushButton("Delete",this);
    layout->addWidget(pBD);
    mappers.at(DEL)->setMapping(pBD,i);
    connect(pBD, SIGNAL(clicked()), mappers.at(DEL), SLOT(map()));

    widget->setLayout(layout);

    return widget;
}

void QDateSessionsManager::editSession(unsigned int i)
{
    QEditSession *w = new QEditSession(sessions.at(i),true,0);
    w->show();
    connect(w,SIGNAL(finished()),this,SLOT(loadUI()));
}

void QDateSessionsManager::deleteSession(unsigned int i)
{
    QString text = QString("Are you sure you want to delete the session :\n") + QString(this->sessions.at(i)->toString().c_str());
    int reponse = QMessageBox::question(this,"Delete file",text);

    if(reponse == QMessageBox::Yes)
    {
        QFile file(dir->entryInfoList().at(i).absoluteFilePath());
        file.remove();
        loadUI();
        this->resize(0,0);
    }
}

void QDateSessionsManager::addSession()
{
    Session *session = new Session();

    /*Create ID*/
    unsigned int id = n_files;

    while(sessionExists(date,id))
    {
        id++;
    }

    /*Loads the new session*/

    session->setID(id);
    session->setDate(date.toString(DATE_TYPE).toStdString());
    QEditSession *w = new QEditSession(session,true,0);
    w->show();
    connect(w,SIGNAL(finished()),this,SLOT(loadUI()));
}

void QDateSessionsManager::clearSessionsUI()
{
    QWidget* item;
    while ( !childWidgets.isEmpty() && ( (item = childWidgets.takeFirst()) != 0 ) )
    {
        this->layout()->removeWidget(item);
        delete item; // It works no matter where the item is
    }
    delete this->layout();
    childWidgets.clear();
}
