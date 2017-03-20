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

