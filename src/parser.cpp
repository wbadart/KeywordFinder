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

    std::map<std::string, unsigned> result;

    // Load web_result and search terms into FileObjects
    FileObj site(fname_result), terms(fname_search);

    // Convert to set in O(n)
    std::set<std::string> web_words = site.to_set();
    for(std::string word: web_words)
        result[word] = 0;

    // Count occurrences of search terms
    for(std::string term: terms.get_items())
        result[term] += web_words.count(term);

    args->result_parse = result;

}

