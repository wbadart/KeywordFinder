/**
 * config.hpp
 *
 * Class interface of config file parser.
 *
 * Badart, Cat
 * Badart, Will
 * created: MAR 2017
 */

#include <fstream>
#include <iostream>
#include <string>

class Config{

    public:

        // Default constructor (takes filename of config file)
        Config(std::string fname="config");

        // Print configuration to ostream
        std::ostream& dump(std::ostream& stream=std::cerr);

    // private:

        // Time in seconds between fetches of the various sites
        unsigned PERIOD_FETCH;

        // Number of fetch threads
        size_t NUM_FETCH;

        // Number of parsing threads
        size_t NUM_PARSE;

        // Name of file containing target search strings
        std::string SEARCH_FILE;

        // Name of file containing target sites
        std::string SITE_FILE;
};

