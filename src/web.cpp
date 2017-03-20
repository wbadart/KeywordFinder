/**
 * web.cpp
 *
 * Web class implementation.
 *
 * Badart, Cat
 * Badart, Will
 * created: MAR 2017
 */

#include "./web.hpp"

Web::Web():curl(curl_easy_init()){}
Web::~Web(){curl_easy_cleanup(curl);}

std::string Web::exec(std::string url){

    // Set target URL and redirect behavior (follow redirect)
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    std::cerr << "web:Fetching URL \"" << url << "\"\n";

    // Create and open temporary result file
    char *fname = strdup("/tmp/web_resultXXXXXX");
    int fd = mkstemp(fname); FILE *file = fdopen(fd, "w");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)file);

    // Execute, report results, and return filename
    result = curl_easy_perform(curl);
    fclose(file);

    std::cerr << (result == CURLE_OK
                    ? std::string("web:curl_easy_perform() succeeded:")
                        + fname
                    : std::string("web:curl_easy_perform() failed: ")
                        + curl_easy_strerror(result))
              << std::endl;

    return std::string(fname);
}

