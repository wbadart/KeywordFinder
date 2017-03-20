/**
 * main.cpp
 *
 * Entry file of project program.
 *
 * Badart, Cat
 * Badart, Will
 * created: MAR 2017
 */

#include <cstdlib>  // exit
#include <iostream>
#include <string>

#include "read_file.h"
#include "config.hpp"
#include "web.hpp"

void usage(int status=0);

int main(int argc, char *argv[]){

    if(argc == 2 && (std::string(argv[1]) == "-h"
                 ||  std::string(argv[1]) == "--help"))
        usage();

    Config config(argc == 2 ? argv[1] : "./config"); Web web;
    FileObj sites(config.SITE_FILE);
    for(auto x: sites.get_items())
        std::cout << "web:file:" << web.exec(x) << std::endl;

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

