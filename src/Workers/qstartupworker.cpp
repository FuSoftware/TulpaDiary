#include "qstartupworker.h"

QStartupWorker::QStartupWorker(QObject *parent) : QObject(parent)
{

}

void QStartupWorker::process()
{
    int res = main_routine();
    emit finished();
}

int QStartupWorker::main_routine()
{
    //Contacts the remote server to update the database regarding the number of users.
    //It sends the version of the software. The PHP page uses the IP and the current time

    //I might use a similar way in the future to remotely save your tulpas so you'll just have to sync an account.

    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QNetworkRequest request;

    QUrl url("http://florentuguet.net16.net/tulpadiary/software.php"); //Main URL
    //QUrl url("http://florentuguet.net16.net/tulpadiary/software-test\.php"); //Test URL
    QUrlQuery params;

    request.setUrl(url.toString());
    request.setRawHeader("User-Agent", "TulpaDiary");
    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");

    params.addQueryItem("version", QString(VERSION));
    params.addQueryItem("build", QString::number(BUILD));

    if(DEBUG){params.addQueryItem("type", "debug");}
    else{params.addQueryItem("type", "release");}

    QByteArray data;
    data.append(params.toString()); //POST params

    QNetworkReply* m_pReply = manager->post(request,data);

    QTimer timer(0);
    timer.setInterval(5000); //5s timeout

    QObject::connect(&timer, SIGNAL(timeout()),m_pReply, SLOT(abort()));

    QEventLoop loop;
    QObject::connect(m_pReply, SIGNAL(finished()),&loop, SLOT(quit()));
    loop.exec();


    if(m_pReply->error() != QNetworkReply::NoError)
    {
        outputInfo(L_ERROR,std::string("Error when sending version : ") + m_pReply->errorString().toStdString());
        return m_pReply->error();
    }

    bool ok;

    qDebug() << "Version :"<<m_pReply->rawHeader("X-Version") <<m_pReply->rawHeader("X-Build");
    qDebug()<< m_pReply->rawHeaderList();

    QString lastBuild_s = QString(m_pReply->rawHeader("X-Build"));
    QString version = QString(m_pReply->rawHeader("X-Version"));

    int lastBuild = lastBuild_s.toInt(&ok);

    if(!ok)
    {
        //Logs the HTTP response
        outputInfo(L_ERROR,std::string("Retrieved build isn't a String : ") + lastBuild_s.toStdString());
        outputInfo(L_ERROR,std::string("Full string : ") + QString(m_pReply->readAll()).toStdString());
    }
    else
    {
        //Checks the update status
        if(lastBuild > BUILD)
        {
            //Update needed
            outputInfo(L_DEBUG,std::string("Update required : ") + std::string(VERSION) + std::string(" -> ") + version.toStdString());

            int rep = QMessageBox::question(0,"Update","Version " + version  + " is available, do you wish to update ?\nYou will need to restart the software after the update is complete.\nChangelog: https://community.tulpa.info/thread-software-tulpadiary", QMessageBox ::Yes | QMessageBox::No);
            if (rep == QMessageBox::Yes)
            {
                QDownloadWidget *down = new QDownloadWidget(0,true);
                down->show();
                down->download(URL_EXECUTABLE,EXECUTABLE_DL,true);
            }
        }
        else
        {
            //Update not needed
            outputInfo(L_DEBUG,std::string("You have the latest version"));
        }
    }

    return 0;
}

