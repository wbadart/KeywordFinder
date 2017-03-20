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

#include <curl/curl.h>

class Web{
    public:
        Web();
        ~Web();
    private:
        CURL    *curl;
        CURLcode result;
};

#endif

