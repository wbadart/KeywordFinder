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
void *thread_function_proxy(void *args);

int main(int argc, char *argv[]){

    if(argc == 2 && (std::string(argv[1]) == "-h"
                 ||  std::string(argv[1]) == "--help"))
        usage();
    /*
     *  signal(____, ____)
     *  while(keep looping) {
     *      signal -> keep looping = 0
     *      lock
     *      while(____)
     *  }
     *  signal:
     *      keep looping = 0
     *      for all the threads that happen to be out there:
     *          pthread_cond_broadcast
     */
    Config config(argc == 2 ? argv[1] : "./config");
    FileObject sites(config.SITE_FILE);

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

void *thread_function_proxy(void* args){
    task_arg_t *cast_args = (task_arg_t*)args;
    cast_args->target->exec(cast_args);
    return nullptr;
}

