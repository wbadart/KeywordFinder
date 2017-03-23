/**
 * main.cpp
 *
 * Entry file of project program.
 *
 * Badart, Cat
 * Badart, Will
 * created: MAR 2017
 */

#include <csignal>
#include <cstdlib>  // exit
#include <iostream>
#include <string>

#include "config.hpp"
#include "parser.hpp"
#include "file_object.hpp"
#include "task_queue.hpp"
#include "web.hpp"

void usage(int status=0);

int main(int argc, char *argv[]){

    if(argc == 2 && (std::string(argv[1]) == "-h"
                 ||  std::string(argv[1]) == "--help"))
        usage();

    Config config(argc == 2 ? argv[1] : "./config");
    FileObject sites(config.SITE_FILE);
    task_arg_t res;

    Web web("http://example.com");
    web.exec(&res);

    Parser parse(res.result_web, config.SEARCH_FILE);
    parse.exec(&res);

    for(auto it: res.result_parse)
        std::cerr << it.first  << ":"
                  << it.second << std::endl;

    return EXIT_SUCCESS;
}

void usage(int status){
    std::cerr << "usage: site-tester CONFIG_FILENAME [ -h ]"
              << std::endl << "Options:" << std::endl
              << "\tCONFIG_FILENAME  Specify name of config file "
              << "(default: \"./config\")" << std::endl
              << "\t-h --help        Print this help message"
              << std::endl;
    exit(status);
}

