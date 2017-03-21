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

#include "task_queue.hpp"
class Task;

class Web: public Task{

    public:

        // Default contructor, sets curl handle to easy_init()
        Web(std::string _url);

        // Deconstructor. Runs easy_cleanup()
        ~Web();

        // Fetch data from "url". Returns result filename or "ERROR"
        void exec(task_arg_t *args);

    private:

        // Internal curl handle
        CURL *curl;

        // Exec result (non-zero means error: use easy_strerror)
        CURLcode result;

        // URL of target resource
        std::string url;
};

#endif

