/**
 * config.cpp
 *
 * Class implementation of config file parser.
 *
 * Badart, Cat
 * Badart, Will
 * created: MAR 2017
 */

#include "config.hpp"

Config::Config(std::string fname):
        PERIOD_FETCH(180)
      , NUM_FETCH(1)
      , NUM_PARSE(1)
      , SEARCH_FILE("Search.txt")
      , SITE_FILE("Sites.txt"){

    std::cerr << "conf:Parsing config file \"" << fname << "\"\n";
    std::ifstream fs(fname); std::string line;

    while(std::getline(fs, line)){

        std::string param, value; size_t i;
        for(i = 0; i < line.size() && line[i] != '='; i++)
            param += line[i];
        for(i += 1; i < line.size() && line[i] != '\n'; i++)
            value += line[i];

        if(param == "PERIOD_FETCH")
            PERIOD_FETCH = std::stoi(value);
        else if(param == "NUM_FETCH")
            NUM_FETCH = std::stoi(value);
        else if(param == "NUM_PARSE")
            NUM_PARSE = std::stoi(value);
        else if(param == "SEARCH_FILE")
            SEARCH_FILE = value;
        else if(param == "SITE_FILE")
            SITE_FILE = value;
        else std::cerr << "conf:Parameter \"" << param
                       << "\" not recognized. Ignoring\n";
    }

    std::cerr << *this;
}

std::ostream& operator<<(std::ostream& stream, const Config& c){
    stream << "conf:Program configuration:" << std::endl
           << "conf:\tPERIOD_FETCH: " << c.PERIOD_FETCH << std::endl
           << "conf:\tNUM_FETCH:    " << c.NUM_FETCH    << std::endl
           << "conf:\tNUM_PARSE:    " << c.NUM_PARSE    << std::endl
           << "conf:\tSEARCH_FILE:  " << c.SEARCH_FILE  << std::endl
           << "conf:\tSITE_FILE:    " << c.SITE_FILE    << std::endl;
    return stream;
}

