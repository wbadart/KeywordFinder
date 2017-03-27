/**
 * task_queue.hpp
 *
 * Class interface of thread-safe task queue.
 *
 * Badart, Cat
 * Badart, Will
 * created: MAR 2017
 */

#ifndef _H_TASKQUEUE
#define _H_TASKQUEUE

#include <ctime>
#include <deque>
#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>

#include "config.hpp"

class Task;

typedef struct _task_arg{
    Task       *target;
    std::string result;
    time_t      started;
} task_arg_t;

class Task{

    public:

        // This should be the time consuming work
        // done by the thread
        virtual void exec(task_arg_t*) = 0;

        // URL of target resource
        std::string url;

    private:
};

class TaskQueue{

    public:

        // Constructor allocates threads and args
        TaskQueue(unsigned _MAX_THREADS);

        // Deconstructor taketh away
        ~TaskQueue();

        // Set next queue member
        void pipe_to(TaskQueue*);

        // Check if queue complete
        bool done();

        // Track Task thread results
        std::vector<std::string> results;

        // Attach a configuration for convenience
        Config *config;

        // Conditional variable to lock shared data structure
        static pthread_cond_t  cond;
        static pthread_mutex_t mux;


        //===================
        // Templated methods
        //===================

        // Add task, broadcast task ready (TODO: delete t)
        //     Template param is the type of Task being exec'd
        template<typename task_T>
        void push(std::string s){
            queue.push_front(new task_T(s)); }

        // Run all tasks
        //     Template param is the type of task next in pipe
        template<typename next_T>
        void run(){

            // Wait for the signal to begin
            //pthread_cond_wait(&cond, &mux);

            // Flush the queue, executing tasks
            while(!queue.empty()){

                std::cerr << "task:Processing " << queue.size()
                          << " tasks" << std::endl;

                // While you are under max threads
                //     and have another task in queue
                for(size_t i = 0;
                         nthreads < MAX_THREADS
                      && !queue.empty(); i++){
                    std::cerr << "task:Spawning thread #"
                              << nthreads <<std::endl;
                    args[i].target = queue.back(); queue.pop_back();
                    pthread_create(threads + i
                                 , nullptr
                                 , thread_function_proxy
                                 , args + i);
                    nthreads++;
                }

                std::cerr << "task:Spawned" << nthreads
                          << " threads" << std::endl;

                // Once max threads reached or queue empty
                //     Carefule: nthreads is unsigned
                while(nthreads--){

                    std::cerr << "task:Joining thread #"
                              << nthreads << std::endl;
                    pthread_join(threads[nthreads]
                              , (void**)nullptr);
                    results.push_back(args[nthreads].result);

                    // If there's another step in the pipeline
                    if(next)
                        next->push<next_T>(
                            args[nthreads].target->url
                          + "|"
                          + std::to_string(args[nthreads].started)
                          + "|"
                          + args[nthreads].result
                          + "|"
                          + config->SEARCH_FILE);

                }
                nthreads = 0;
            }

            std::cerr << "task:Queue flushed" << std::endl;
            if(next){
                std::cerr << "task:Continuing pipeline\n";
                next->run<next_T>();
            } else{
                std::cerr << "task:Signalling on cond\n";
                pthread_cond_signal(&cond);
            }
        }

    private:

        // Queue backend (using deque for operator[])
        std::deque<Task*> queue;

        // Track # of live threads and max allowed threads
        unsigned MAX_THREADS;
        unsigned nthreads;

        // Thread and argument arrays
        pthread_t  *threads;
        task_arg_t *args;

        // Next queue in pipeline; task result target
        TaskQueue *next;

        // Wrapper to Task::exec
        static void *thread_function_proxy(void* args);

};

#endif

