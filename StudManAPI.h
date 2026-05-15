#ifndef STUDMAN_API_H
#define STUDMAN_API_H

#ifdef _WIN32
    #ifdef STUDMAN_EXPORTS
        #define STUDMAN_API __declspec(dllexport)
    #else
        #define STUDMAN_API __declspec(dllimport)
    #endif
#else
    #define STUDMAN_API
#endif

#endif