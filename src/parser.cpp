/**
 * parser.cpp
 *
 * Responsible for finding keywords inside
 * web_result files.
 *
 * Badart, Cat
 * Badart, Will
 * created: MAR 2017
 */

#include "./read_file.h"
#include "./parser.hpp"

Parser::Parser(std::string _fname_result
             , std::string _fname_search):
        fname_result(_fname_result)
      , fname_search(_fname_search){}

Parser::~Parser(){}

void Parser::exec(task_arg_t *args){

    // Load web_result and search terms into FileObjects
    FileObj site(fname_result), terms(fname_search);
    args->result_parse = site.to_count(terms.to_set());

}

