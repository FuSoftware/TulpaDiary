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
