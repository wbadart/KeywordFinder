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
#include "read_file.h"
#include "task_queue.hpp"
#include "web.hpp"

void usage(int status=0);

int main(int argc, char *argv[]){

    if(argc == 2 && (std::string(argv[1]) == "-h"
                 ||  std::string(argv[1]) == "--help"))
        usage();

    Config config(argc == 2 ? argv[1] : "./config");
    FileObj sites(config.SITE_FILE);

    Web web("http://example.com");
    task_arg_t res_web, res_parse;
    web.exec(&res_web);
    Parser parse(res_web.result_web, config.SITE_FILE);
    parse.exec(&res_parse);

    for(auto it: res_parse.result_parse)
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

