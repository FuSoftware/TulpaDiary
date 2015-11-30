#ifndef CONSTANTES
#define CONSTANTES

#define DEBUG 0

#define APP_NAME "TulpaDiary"
#define VERSION "0.3.2.0"

#define DATE_TYPE "yyyyMMdd"
#define DATE_TYPE_OUTPUT "dd/MM/yyyy"

/*Folders*/
#if DEBUG
    #if __WIN32
        #define TULPA_FOLDER "F:/My Programs/C++/TulpaDiary/data/tulpas/"
        #define SESSION_FOLDER "F:/My Programs/C++/TulpaDiary/data/sessions/"
        #define DATA_FOLDER "F:/My Programs/C++/TulpaDiary/data/"
        #define LOG_FILE "F:/My Programs/C++/TulpaDiary/logfile.log"
    #elif __linux
        #define TULPA_FOLDER "/usr/share/tulpadiary/data/tulpas/"
        #define SESSION_FOLDER "/usr/share/tulpadiary/data/sessions/"
        #define DATA_FOLDER "/usr/share/tulpadiary/data/"
        #define LOG_FILE "/usr/share/tulpadiary/logfile.log"
    #endif
#else
    #define SESSION_FOLDER "data/sessions/"
    #define TULPA_FOLDER "data/tulpas/"
    #define DATA_FOLDER "data/"
    #define LOG_FILE "logfile.log"
#endif

#define URL_GUIDELIST "https://raw.githubusercontent.com/FlorentUguet/TulpaDiary/master/guidelist.json"

enum OutputLevel{
    L_DEBUG = 0,
    L_VERBOSE,
    L_WARNING,
    L_ERROR
};

#endif // CONSTANTES

