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

#include <map>
#include <pthread.h>
#include <queue>
#include <string>

class Task;

typedef struct _task_arg{
    Task* target;
    std::map<std::string, unsigned> result_parse;
    std::string                     result_web;
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

        // Add task, broadcast task ready (TODO: delete t)
        void push(Task *t);

        // Set next queue member
        void pipe_to(TaskQueue*);

    private:

        // Queue backend
        std::queue<Task*> queue;

        // Track # of live threads and max allowed threads
        unsigned MAX_THREADS;
        unsigned active_threads;

        // Thread and argument arrays
        pthread_t  *threads;
        task_arg_t *args;

        // Next queue in pipeline; task result target
        TaskQueue *next;

        // Conditional variable to lock shared data structure
        pthread_cond_t  cond;
        pthread_mutex_t mux;
};

#endif

