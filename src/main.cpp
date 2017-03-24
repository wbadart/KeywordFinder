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
#include <pthread.h>
#include <string>
#include <unistd.h> //alarm

#include "config.hpp"
#include "file_object.hpp"
#include "parser.hpp"
#include "task_queue.hpp"
#include "web.hpp"

void usage(int status=0);
void handle_SIGALRM(int);
void handle_SIGINT(int);

// Wrap the strings cells of CSV in quotes
std::string proc_fields(std::string);

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

    // Load program configutaion, use default
    //     if command line argument not given
    config = new Config(argc == 2 ? argv[1] : "./config");

    // Load up list of target websites
    FileObject sites(config->SITE_FILE);

    // Initialize task queues
    TaskQueue fetch(config->NUM_FETCH), parse(config->NUM_PARSE);
    fetch.pipe_to(&parse); fetch.config = config;

    // Register signal handlers
    signal(SIGALRM, handle_SIGALRM);
    signal(SIGINT,  handle_SIGINT);
    signal(SIGHUP,  handle_SIGINT);

    // Signal first period to begin, track number of runs
    alarm(1); unsigned run_number = 0;

    // Run main execution
    while(g_keep_looping){

        // If we're ready for the next cycle to begin...
        if(!g_trigger_period) continue;
        g_trigger_period = false; run_number++;
        std::cerr << "main:Starting new period" << std::endl;

        // Load up sites into queue and let
        //     everything just fall into place
        // Template param is the type of task being exec'd
        for(std::string site: sites) fetch.push<Web>(site);

        // Template param is the next Task type in the pipeline
        fetch.run<Parser>();

        // Wait for last pipeline component (parsing) to finish
        while(!fetch.done() && !parse.done())
            pthread_cond_wait(&TaskQueue::cond, &TaskQueue::mux);
        std::cerr << "main:Cleared cond_wait" << std::endl;

        // Concatenate parse results
        std::string fname(std::to_string(run_number) + ".csv");
        std::ofstream fs(fname);

        // Column labels
        fs << "Time,Phrase,Site,Count" << std::endl;

        // The actual data (stored in tmp files)
        for(std::string res_fname: parse.results)
            for(std::string line: FileObject(res_fname))
                fs << line << std::endl;

        std::cout << "main:Emitted results to \"" << fname
                  << "\"" << std::endl;
        fs.close();

        // Generate HTML output
        FileObject header("./partials/head.html")
                 , footer("./partials/foot.html")
                 , script("./partials/script.js");

        std::ofstream fs_index("./index.html")
                    , fs_script("./script.js");

        // Tell JS how often to refresh and seed with data
        fs_script << "var PERIOD = " << config->PERIOD_FETCH << ";\n"
                  << "var CSV = ["   << std::endl;
        for(std::string res_fname: parse.results)
            for(std::string line: FileObject(res_fname))
                fs_script << "[" << proc_fields(line) << "]," << std::endl;
        fs_script << "];" << std::endl;

        // Add in the rest of the script template
        for(std::string line: script)
            fs_script << line << std::endl;
        fs_script.close();

        // Create the index file
        for(std::string line: header)
            fs_index << line;
        for(std::string line: footer)
            fs_index << line;
        fs_index.close();
        std::cerr << "main:Report index.html generated" << std::endl;
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
    g_trigger_period = true;
    alarm(config->PERIOD_FETCH);
}

void handle_SIGINT(int s){
    g_keep_looping = false;
    std::cout << "main:Goodbye!" << std::endl;
    //broadcast all the current threads
    //pthread_cond_broadcast(pthread_cond_t *cond);
}

std::string proc_fields(std::string s){

    // 1234,example,http://nd.edu,3
    //      ^      ^^            ^
    size_t cursor = 0;

    // Surround phrase in quotes
    while(s[cursor++] != ',');
    s.insert(cursor++, "'");
    while(s[cursor++ + 1] != ',');
    s.insert(cursor++, "'");

    // Surround URL in quotes
    while(s[cursor++] != ',');
    s.insert(cursor++, "'");
    while(s[cursor++ + 1] != ',');
    s.insert(cursor, "'");

    return s;
}

