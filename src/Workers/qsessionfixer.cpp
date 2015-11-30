#include "qsessionfixer.h"

QSessionFixer::QSessionFixer(QWidget *parent) : QWidget(parent)
{
    f = false;
    calendar = new QCalendarBox(0);
    calendar->setModal(true);
    connect(calendar->getCalendar(),SIGNAL(activated(QDate)),this,SLOT(fixLostSession(QDate)));
}

void QSessionFixer::fix()
{
    dir = new QDir(SESSION_FOLDER);
    dir->setFilter(QDir::Files|QDir::NoDotAndDotDot);
    index_max = dir->entryList().size();
    index = 0;

    if(dir->entryList().size() != 0)
    {
        QMessageBox::information(this,"Session Fixer","You will now have to fix the previously set sessions.\nPlease select the corresponding date of each session in the calendar that will show up.\nSorry for the inconvenience.");
        loadLostSession(dir->entryInfoList().at(index).absoluteFilePath());
        terminate();
    }
    else
    {
        fixSessionIds();
        terminate();
    }
}

bool QSessionFixer::isFinished()
{
    return this->f;
}


void QSessionFixer::terminate()
{
    outputInfo(L_DEBUG,"Session Fixer finished");
    f = true;
    emit finished();
    this->deleteLater();
}

void QSessionFixer::loadLostSession(QString path)
{
    json_path = path;
    root = loadJSONFile(path.toStdString().c_str());
    calendar->setData(root);
    calendar->show();
}

void QSessionFixer::fixLostSession(QDate date)
{
    outputInfo(L_DEBUG,"Finding and fixing lost sessions");
    calendar->hide();
    root["date"] = date.toString(DATE_TYPE).toStdString();

    QString folder = QString(SESSION_FOLDER) + date.toString(DATE_TYPE) + QString("/");
    QDir dateFolder(folder);
    dateFolder.setFilter(QDir::Files|QDir::NoDotAndDotDot);

    checkFolder(folder.toStdString());

    unsigned int id = dateFolder.entryList().size();

    while(sessionExists(date,id))
    {
        id++;
    }

    root["id"] = id;

    QString new_path = folder + QString::number(id) + QString(".json");

    saveJSONFile(root,json_path.toStdString().c_str());

    QFile file(json_path);

    file.rename(new_path);

    index++;

    if(index < index_max)
    {
        loadLostSession(dir->entryInfoList().at(index).absoluteFilePath());
    }
    else
    {
        QMessageBox::information(this,"Session Fixer","Sessions fixed. Please be aware that until 1.0, there is a small chance you might need to do it again.");
        fixSessionIds();
    }
}

void QSessionFixer::fixSessionIds()
{
    /*Correctly inputs session IDs for each tulpa*/
    /*Clears each tulpa's IDs*/
    outputInfo(L_DEBUG,"Loading sessions into tulpas");

    QDir tulpa_folder(TULPA_FOLDER);
    tulpa_folder.setFilter(QDir::Files|QDir::NoDotAndDotDot);
    int n_tulpa = tulpa_folder.entryList().size();

    for(int i=1;i<n_tulpa;i++)
    {
        Tulpa tulpa(tulpa_folder.entryInfoList().at(i).baseName().toStdString(),false);
        tulpa.clearSessions();
        tulpa.save();
    }

    /*Work*/
    QDir session_folder(SESSION_FOLDER);
    Session *session;
    session_folder.setFilter(QDir::Dirs|QDir::NoDotAndDotDot);
    int n_dates = session_folder.entryList().size();
    bool folder_ok = false;

    for(int i=0;i<n_dates;i++)
    {
        /*For each subfolder*/
        QDir date_dir(session_folder.entryInfoList().at(i).absoluteFilePath());

        date_dir.dirName().toInt(&folder_ok);//Checks if the name is int
        if(folder_ok)
        {
            /*If the folder has a numeric name*/
            date_dir.setFilter(QDir::Files|QDir::NoDotAndDotDot);
            int n_sessions = date_dir.entryList().size();

            for(int j=0;j<n_sessions;j++)
            {
                /*For each file*/
                QString path = date_dir.entryInfoList().at(j).absoluteFilePath();
                session = new Session(path.toStdString());
                fixID(session,date_dir.dirName());
                delete session;
            }
        }
    }
}

void QSessionFixer::fixID(Session* session, QString folder_id)
{
    std::string id = folder_id.toStdString() + intToString(session->getId());
    session_index = new SessionIndex(id);

    if(session->hasTulpa())
    {
        Tulpa tulpa(session->getTulpaName());
        tulpa.addSessions(*session);
        tulpa.save();
        qDebug() << "Added session" << atoi(id.c_str()) << "to" << tulpa.getName().c_str();
    }
}

