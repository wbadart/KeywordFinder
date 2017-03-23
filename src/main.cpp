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
#include "file_object.hpp"
#include "parser.hpp"
#include "task_queue.hpp"
#include "web.hpp"

void usage(int status=0);
void *thread_function_proxy(void *args);
void handle_SIGALRM(int);
void handle_SIGINT(int);

bool g_keep_looping = true;
bool g_trigger_period = false;

Config *config;

int main(int argc, char *argv[]){

    // Verify correct number of arguments, check for help flag
    if(argc > 3){
        std::cerr << "error:Too many arguments" << std::endl;
        exit(1);
    } else if(argc == 2
            && (std::string(argv[1]) == "-h"
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
    // Load program configutaion, use default
    //     if command line argument not given
    config = new Config(argc == 2 ? argv[1] : "./config");

    // Load up list of target websites
    FileObject sites(config->SITE_FILE);

    // Initialize task queues
    TaskQueue fetch(config->NUM_FETCH), parse(config->NUM_PARSE);
    fetch.pipe_to(&parse);

    // Register signal handlers
    signal(SIGALRM, handle_SIGALRM);
    signal(SIGINT,  handle_SIGINT);

    // Signal first period to begin
    alarm(1);

    // Run main execution
    while(g_keep_looping){

        // If we're ready for the next cycle to begin...
        if(!g_trigger_period) continue;
        g_trigger_period = false;

        // Load up sites into queue and let
        //     everything just fall into place
        for(std::string site: sites)
            fetch.push<Web>(site);
        fetch.run<Parser>();
    }

    // Clean up and go home
    delete config;
    return EXIT_SUCCESS;
}

void usage(int status){
    std::cerr << "usage: site-tester CONFIG_FILENAME [ -h ]"
              << std::endl << "Options:" << std::endl
              << "\tCONFIG_FILENAME  Specify name of config file"
              << " (default: \"./config\")" << std::endl
              << "\t-h --help        Print this help message"
              << std::endl;
    exit(status);
}

void handle_SIGALRM(int s) {
    std::cout << "main:new period starting" << std::endl;
    g_trigger_period = true;
    alarm(config->PERIOD_FETCH);
}

void handle_SIGINT(int s){
    g_keep_looping = false;
    //broadcast all the current threads
    //pthread_cond_broadcast(pthread_cond_t *cond);
}

