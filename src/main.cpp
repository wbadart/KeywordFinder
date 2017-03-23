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
#include <pthread.h>
#include <string>

#include "config.hpp"
#include "parser.hpp"
#include "file_object.hpp"
#include "task_queue.hpp"
#include "web.hpp"

void usage(int status=0);
void *thread_proxy(task_arg_t*);

Web *fetchers;

int main(int argc, char *argv[]){

    if(argc == 2 && (std::string(argv[1]) == "-h"
                 ||  std::string(argv[1]) == "--help"))
        usage();

    Config config(argc == 2 ? argv[1] : "./config");
    FileObject sites(config.SITE_FILE);
    task_arg_t res;

    pthread_t *fetch_threads = new pthread_t[
                sizeof(pthread_t) * config.NUM_FETCH ]
            , *parse_threads = new pthread_t[
                sizeof(pthread_t) * config.NUM_PARSE ];

    task_arg_t *fetch_args = new task_arg_t[
                sizeof(task_arg_t) * config.NUM_FETCH ]
             , *parse_args = new task_arg_t[
                sizeof(task_arg_t) * config.NUM_PARSE ];

    fetchers = new Web[sites.size()];
    for(size_t i = 0; i < sites.size(); i++)
        fetchers[i].set_url(sites[i]);

    for(size_t i = 0; i < config.NUM_FETCH; i++){
        fetch_args[i].target = fetchers + i;
        pthread_create(fetch_threads + i
                     , NULL
                     , thread_proxy
                     , fetch_args + i
        );
    }

    Web web("http://example.com");
    web.exec(&res);

    Parser parse(res.result_web, config.SEARCH_FILE);
    parse.exec(&res);

    for(auto it: res.result_parse)
        std::cerr << it.first  << ":"
                  << it.second << std::endl;

    delete [] fetch_threads; delete [] parse_threads;
    delete [] fetch_args;    delete [] parse_args;

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

void *thread_proxy(task_arg_t* args){
    args->target->exec(args);
    return nullptr;
}

