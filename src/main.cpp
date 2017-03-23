/**
 * main.cpp
 *
 * Entry file of project program.
 *
 * Badart, Cat
 * Badart, Will
 * created: MAR 2017
 */

#include <csignal>  // signal
#include <cstdlib>  // exit
#include <iostream>
#include <string>
#include <unistd.h> //alarm

#include "config.hpp"
#include "parser.hpp"
#include "file_object.hpp"
#include "task_queue.hpp"
#include "web.hpp"

void usage(int status=0);
void *thread_proxy(task_arg_t*);
void *thread_function_proxy(void *args);
void alarm_handler(int);
void intHandler(int);

Web *fetchers;
char KeepLooping = 1;

int main(int argc, char *argv[]){
    //verify correct number of arguments
    if(argc == 2 && (std::string(argv[1]) == "-h"
                 ||  std::string(argv[1]) == "--help"))
        usage();
    /*
     *  signal(____, ____)
     *  while(keep looping) {
     *      lock
     *      while(____)
     *  }
     *  signal:
     *      keep looping = 0
     *      for all the threads that happen to be out there:
     *          pthread_cond_broadcast
     */
    Config config(argc == 2 ? argv[1] : "./config");
    //set up alarm handler
    signal(SIGALRM, alarm_handler);
    alarm(config.PERIOD_FETCH);
    //set up interrupt handler
    signal(SIGINT, intHandler);
    //while(KeepLooping)
    //create sites file object
    FileObject sites(config.SITE_FILE);
    task_arg_t res;
    /*
     *  struct thread_args** args = malloc(sizeof(struct thread_args) * nthreads);
     *  pthread_t * threads = malloc(sizeof(pthread_t) * nthreads);
     *  for(int i = 0; i < nthreads; i++) {
     *      args[i] = malloc(sizeof(struct thread_args));
     *      args[i]->data = value...
     *      pthread_create(&threads[i], NULL, (void *) thread_proxy, (void *) args[i]);
     *  }
     *  for(int i = 0; i < nthreads; i++)
     *      pthread_join(threads[i], NULL);
     */
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
                     , thread_function_proxy
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

void *thread_function_proxy(void* args){
    task_arg_t *cast_args = (task_arg_t*)args;
    cast_args->target->exec(cast_args);
    return nullptr;
}

void alarm_handler(int s) {
    std::cout << "new period starting" << std::endl;
    alarm(180);
    signal(SIGALRM, alarm_handler);
}

void intHandler(int s){
    KeepLooping = 0;
    //broadcast all the current threads
}
