#ifndef CONSTANTES
#define CONSTANTES

#define DEBUG 1

#define VERSION 0.0.1.1

/*Folders*/
#if DEBUG
    #if __WIN32
        #define TULPA_FOLDER "F:/My Programs/C++/TulpaDiary/data/tulpas/"
        #define SESSION_FOLDER "F:/My Programs/C++/TulpaDiary/data/sessions/"
    #elif __linux
        #define TULPA_FOLDER "/usr/share/TulpaDiary/data/tulpas/"
        #define SESSION_FOLDER "/usr/share/TulpaDiary/data/sessions/"
    #endif
#else
    #define SESSION_FOLDER "data/sessions/"
    #define TULPA_FOLDER "data/tulpas/"
#endif

enum OutputLevel{
    L_DEBUG = 0,
    L_VERBOSE,
    L_WARNING,
    L_ERROR
};

#endif // CONSTANTES

