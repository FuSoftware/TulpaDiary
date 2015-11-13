#ifndef CONSTANTES
#define CONSTANTES

#define DEBUG 0

#define APP_NAME "TulpaDiary"
#define VERSION "0.2.1.0"

/*Folders*/
#if DEBUG
    #if __WIN32
        #define TULPA_FOLDER "F:/My Programs/C++/TulpaDiary/data/tulpas/"
        #define SESSION_FOLDER "F:/My Programs/C++/TulpaDiary/data/sessions/"
        #define DATA_FOLDER "F:/My Programs/C++/TulpaDiary/data/"
    #elif __linux
        #define TULPA_FOLDER "/usr/share/TulpaDiary/data/tulpas/"
        #define SESSION_FOLDER "/usr/share/TulpaDiary/data/sessions/"
        #define DATA_FOLDER "/usr/share/TulpaDiary/data/"
    #endif
#else
    #define SESSION_FOLDER "data/sessions/"
    #define TULPA_FOLDER "data/tulpas/"
    #define DATA_FOLDER "data/"
#endif

#define URL_GUIDELIST "https://raw.githubusercontent.com/FlorentUguet/TulpaDiary/master/guidelist.json"

enum OutputLevel{
    L_DEBUG = 0,
    L_VERBOSE,
    L_WARNING,
    L_ERROR
};

#endif // CONSTANTES

