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

#include "file_object.hpp"
#include "parser.hpp"

Parser::Parser(std::string _fname_result
             , std::string _fname_search):
        fname_result(_fname_result)
      , fname_search(_fname_search){}

Parser::~Parser(){}

void Parser::exec(task_arg_t *args){

    // Load web_result and search terms into FileObjects
    FileObject site(fname_result), terms_f(fname_search);
    std::set<std::string> terms = terms_f.get_tokens();

    std::cerr << "parse:Searching for terms from \""
              << fname_search << "\"" << std::endl
              << "parse:\tin file \"" << fname_result
              << "\"" << std::endl;

    // Initialize the result data structure
    std::map<std::string, unsigned> result;
    for(std::string t: terms) result[t] = 0;

    // For each word on each line, inc result if term found
    for(std::string line: site.get_lines())
        for(std::string tok: terms_f.get_tokens(line))
            if(terms.count(tok)) result[tok]++;

    for(auto pair: result)
        std::cout << "parse:Found " << pair.second
                  << " occurrences of " << pair.first
                  << std::endl;

    args->result_parse = result;
}

