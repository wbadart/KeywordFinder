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

#include <deque>
#include <map>
#include <pthread.h>
#include <string>

class Task;

typedef struct _task_arg{
    Task       *target;
    std::string result;
} task_arg_t;

class Task{

    public:

        // This should be the time consuming work
        // done by the thread
        virtual void exec(task_arg_t*) = 0;

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

        //===================
        // Templated methods
        //===================

        // Add task, broadcast task ready (TODO: delete t)
        template<typename task_T>
        void push(std::string s){
            queue.push_front(new task_T(s));
        }

        // Run all tasks
        template<typename next_T>
        void run(){

            // Wait for the signal to begin
            pthread_cond_wait(&cond, &mux);

            // Flush the queue, executing tasks
            while(!queue.empty()){

                // While you are under max threads
                //     and have another task in queue
                size_t i;
                for(i = active_threads;
                        i < MAX_THREADS && !queue.empty();
                        i++ && active_threads++){
                    args[i].target = queue.back(); queue.pop_back();
                    pthread_create(threads + i
                                 , nullptr
                                 , thread_function_proxy
                                 , args + i);
                }

                // Once max threads reached or queue empty
                for(i = i; i; i--){
                    pthread_join(threads[i], (void**)nullptr);

                    // If there's another step in the pipeline
                    if(next) next->push<next_T>(args[i].result);
                }

            }
        }

    private:

        // Queue backend (using deque for operator[])
        std::deque<Task*> queue;

        // Track # of live threads and max allowed threads
        unsigned MAX_THREADS;
        unsigned active_threads;

        // Thread and argument arrays
        pthread_t  *threads;
        task_arg_t *args;

        // Next queue in pipeline; task result target
        TaskQueue *next;

        // Conditional variable to lock shared data structure
        static pthread_cond_t  cond;
        static pthread_mutex_t mux;

        // Wrapper to Task::exec
        static void *thread_function_proxy(void* args);

};

#endif

