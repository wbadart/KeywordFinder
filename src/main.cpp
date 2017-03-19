/**
 * main.cpp
 *
 * Entry file of project program.
 *
 * Badart, Cat
 * Badart, Will
 * created: MAR 2017
 */

#include <cstdlib>      // exit
#include <iostream>
#include <string>
#include "config.hpp"

void usage(int status=0);

int main(int argc, char *argv[]){

    std::string config_fname(argc == 2 ? argv[1] : "./config");
    Config config(config_fname);
    usage();

    return 0;
}

void usage(int status){
    std::cerr << "usage: site-tester CONFIG_FILENAME" << std::endl
              << "Options:" << std::endl
              << "\tCONFIG_FILENAME    Specify name of config file "
              << "(default: \"./config\")" << std::endl;
    exit(status);
}

