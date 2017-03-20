/**
 * web.hpp
 *
 * Web class interface. Wraps cURL interactions.
 *
 * Badart, Cat
 * Badart, Will
 * created: MAR 2017
 */

#ifndef _H_WEB
#define _H_WEB

#include <cstdio>       // fdopen
#include <cstdlib>      // mkstemp
#include <cstring>      // strdup
#include <curl/curl.h>
#include <iostream>
#include <string>

class Web{

    public:

        // Default contructor, sets curl handle to easy_init()
        Web();

        // Deconstructor. Runs easu_cleanup()
        ~Web();

        // Fetch data from "url". Returns result filename or "ERROR"
        std::string exec(std::string url);

    private:

        // Internal curl handle
        CURL    *curl;

        // Exec result (non-zero means error: use easy_strerror)
        CURLcode result;
};

#endif

