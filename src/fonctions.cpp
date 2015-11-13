#include "fonctions.h"

#include <QFile>
#include <QDir>

void checkFolder(std::string path)
{
    QDir dirCache1(path.c_str());
    if (!dirCache1.exists()) {
        dirCache1.mkpath(".");
    }
}

bool checkFile(std::string path)
{
    QFile file(path.c_str());
    return file.exists();
}


/*Conversion*/
std::string intToString(int i)
{
    std::stringstream ss;
    std::string s;
    ss << i;
    s = ss.str();

    return s;
}

char* stringToCString(std::string input)
{
    char* output = strdup(input.c_str());
    return output;
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d | %X", &tstruct);

    return buf;
}

std::string currentDate()
{
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );

    std::string output = intToString(now->tm_year + 1900) + std::string("/") + intToString(now->tm_mon + 1) + std::string("/") + intToString(now->tm_mday);
    return output;
}

std::string intToDate(int time)
{
    time_t t = time;   // get time
    struct tm * now = localtime( & t );

    std::string output = intToString(now->tm_year + 1900) + std::string("/") + intToString(now->tm_mon + 1) + std::string("/") + intToString(now->tm_mday);
    return output;
}

void outputInfo(int type, std::string data)
{
    int level;
    std::string type_string;

    switch(type)
    {
    case L_DEBUG:
        type_string = "DEBUG";
        level = 3;
        break;
    case L_VERBOSE:
        type_string = "INFO";
        level = 4;
        break;
    case L_WARNING:
        type_string = "WARNING";
        level = 1;
        break;
    case L_ERROR:
        type_string = "ERROR";
        level = 3;
        break;
    }

    std::cout << "[" << type_string << "]"
              << "[" << currentDateTime() << "]"
              << "|";

    for(int i=0;i<level;i++)
    {
        std::cout <<"-";
    }

    std::cout << "> " << data << std::endl;
}

std::string getFolder(std::string file_path)
{
    return file_path.substr(0,file_path.find_last_of("/"));
}

int downloadFile(const char* url, const char* file, bool override)
{
    QString referer = "Dummy Ref";

    if(fexists(file) && !override)
    {
        //File exists and we don't want to everride
        return 0;
    }
    else
    {
        //Getting redirection

        QUrl file_url = findRedirection(QUrl(QString(url)));

        //Synchronous download
        QNetworkAccessManager *manager = new QNetworkAccessManager;
        QNetworkRequest request;


        request.setUrl(file_url.toString());
        request.setRawHeader("User-Agent", "QBooru");
        //request.setRawHeader("Referer", referer);

        QNetworkReply* m_pReply = manager->get(request);

        QEventLoop loop;
        QObject::connect(m_pReply, SIGNAL(finished()),&loop, SLOT(quit()));
        loop.exec();

        //qDebug() << "Loop finished";

        if(m_pReply->error() != QNetworkReply::NoError)
        {
            QMessageBox::critical(0,"Error",QString("Error while downloading ") + QString(url) + QString(" : ") + m_pReply->errorString());
            return m_pReply->error();
        }

        //qDebug() << "Saving" << QString(file);

        QString file_s = QString(file);

        QFile file(file_s);

        file.open(QIODevice::WriteOnly);
        file.write(m_pReply->readAll());
        file.close();

        return 0;
    }
}

QUrl findRedirection(QUrl url)
{
    QNAMRedirect redirect;
    redirect.processUrl(url.toString());

    QEventLoop loop;
    QObject::connect(&redirect, SIGNAL(finished()),&loop, SLOT(quit()));
    loop.exec();

    return redirect.getLastRedirect();
}

bool fexists(const char *filename)
{
  std::ifstream ifile(filename);
  return ifile;
}
