#ifndef CONSTANTES
#define CONSTANTES

#define DEBUG 0

#define APP_NAME "TulpaDiary"
#define VERSION "0.3.4.1"
#define BUILD 3
//Actual last build :

#define EXIT_CODE_UPDATE 1000

#define DATE_TYPE "yyyyMMdd"
#define DATE_TYPE_OUTPUT "dd/MM/yyyy"

/*Folders*/
#if DEBUG
    #if __WIN32
        #define TULPA_FOLDER "F:/My Programs/C++/TulpaDiary/data/tulpas/"
        #define SESSION_FOLDER "F:/My Programs/C++/TulpaDiary/data/sessions/"
        #define DATA_FOLDER "F:/My Programs/C++/TulpaDiary/data/"
        #define LOG_FILE "F:/My Programs/C++/TulpaDiary/logfile.log"
        #define EXECUTABLE "F:/My Programs/C++/TulpaDiary/TulpaDiary.exe"
        #define EXECUTABLE_DL "F:/My Programs/C++/TulpaDiary/TulpaDiary.dl"
    #elif __linux
        #define TULPA_FOLDER "/usr/share/tulpadiary/data/tulpas/"
        #define SESSION_FOLDER "/usr/share/tulpadiary/data/sessions/"
        #define DATA_FOLDER "/usr/share/tulpadiary/data/"
        #define LOG_FILE "/usr/share/tulpadiary/logfile.log"
        #define EXECUTABLE "/usr/share/tulpadiary/TulpaDiary"
        #define EXECUTABLE_DL "/usr/share/tulpadiary/TulpaDiary.dl"
    #endif
#else
    #define SESSION_FOLDER "data/sessions/"
    #define TULPA_FOLDER "data/tulpas/"
    #define DATA_FOLDER "data/"
    #define LOG_FILE "logfile.log"
    #define EXECUTABLE "TulpaDiary.exe"
    #define EXECUTABLE_DL "TulpaDiary.dl"
#endif

#define URL_GUIDELIST  "https://raw.githubusercontent.com/FlorentUguet/TulpaDiary/master/guidelist.json"
#define URL_EXECUTABLE "https://raw.githubusercontent.com/FlorentUguet/TulpaDiary/master/builds/latest/TulpaDiary.exe"

enum OutputLevel{
    L_DEBUG = 0,
    L_VERBOSE,
    L_WARNING,
    L_ERROR
};

#endif // CONSTANTES

