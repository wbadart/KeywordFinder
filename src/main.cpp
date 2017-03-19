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

void usage(int status=0);

int main(int argc, char *argv[]){

    Config config(argc == 2 ? argv[1] : "./config");
    /* usage(); */

    /* FileObj SitesFile("ExampleSites.txt"); */
	/* SitesFile.print_items(); */

	return EXIT_SUCCESS;
}

void usage(int status){
    std::cerr << "usage: site-tester CONFIG_FILENAME" << std::endl
              << "Options:" << std::endl
              << "\tCONFIG_FILENAME    Specify name of config file "
              << "(default: \"./config\")" << std::endl;
    exit(status);
}

