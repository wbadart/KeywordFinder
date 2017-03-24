/**
 * parser.hpp
 *
 * Class to search web_result files for
 * given keywords.
 *
 * Badart, Cat
 * Badart, Will
 * created: MAR 2017
 */

#ifndef _H_PARSER
#define _H_PARSER

#include <cstring>  // strdup
#include <unistd.h> // close
#include <iostream>
#include <map>
#include <set>
#include <string>

#include "task_queue.hpp"
#include "file_object.hpp"
class Task;

class Parser: public Task{

    public:

        // Constructor: takes target web_result fname
        /* Parser(std::string _fname_result="" */
        /*      , std::string _fname_search=""); */
        Parser(std::string data="");

        // Deconstructor. Yup.
        ~Parser();

        // Read and parse a web result file
        void exec(task_arg_t *args);

    private:

        // Time the corresponding fetch started
        std::string started;

        // Name of target web_result
        std::string fname_result;

        // Name of the search term file
        std::string fname_search;
};

#endif

