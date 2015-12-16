#include "fonctions.h"

#include <QFile>
#include <QDir>

QDate dateFromString(std::string str)
{
    /*!
     * \param Formatted string following the DATE_TYPE format
     *
     * \return QDate object holding the requested date from str
     */

    std::string str_date = str.substr(0,8);

    int y,m,d;

    std::string str_y,str_m,str_d;
    str_y = str_date.substr(0,4); //First 4 chars for year
    str_m = str_date.substr(4,2); //Next 2 chars for month
    str_d = str_date.substr(6,2); //Next 2 chars for day

    y = atoi(str_y.c_str());
    m = atoi(str_m.c_str());
    d = atoi(str_d.c_str());

    QDate date;

    date.setDate(y,m,d);

    return date;
}

bool createMainDirs()
{
    /*!
     * Generates the dirs the program needs to work
     *
     * \return true if the folders were created, false if there's an error (Linux permissions for example)
     */

    outputInfo(L_DEBUG,"Creating main dirs");
    QStringList dir_list;
    dir_list << DATA_FOLDER << SESSION_FOLDER << TULPA_FOLDER;
    for(int i=0; i<dir_list.size();i++)
    {
        checkFolder(dir_list.at(i).toStdString());
        QDir dir(dir_list.at(i));

        if(!dir.exists())
        {
            outputInfo(L_VERBOSE,"Dir " + dir_list.at(i).toStdString() + " could not be created");
            return false;
        }
    }
    outputInfo(L_VERBOSE,"Main dirs existing");
    return true;
}

void checkFolder(std::string path)
{
    //Checks if the folder at "path" exists. If not, creates it
    QDir dirCache1(path.c_str());
    if (!dirCache1.exists()) {
        dirCache1.mkpath(".");
    }
}

bool checkFile(std::string path)
{
    //Checks if the file at "path" exists. Returns existance
    QFile file(path.c_str());
    return file.exists();
}


/*Conversion*/
std::string intToString(unsigned int i)
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
    //Returns the folder path of the specified file
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
        request.setRawHeader("User-Agent", "TulpaDiary");
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
    redirect.processUrl(url.toString()); //Starts processing the URL

    QEventLoop loop;
    QObject::connect(&redirect, SIGNAL(finished()),&loop, SLOT(quit()));
    loop.exec(); //Waits until the process is over

    return redirect.getLastRedirect();
}

bool fexists(const char *filename)
{
  std::ifstream ifile(filename);
  return ifile.is_open();
}

bool sessionExists(QDate date, unsigned int id)
{
    QString file = QString(SESSION_FOLDER) + date.toString(DATE_TYPE) + QString("/") + QString::number(id) + QString(".json");

    return fexists(file.toStdString().c_str());
}
