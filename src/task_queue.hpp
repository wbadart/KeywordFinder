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

#include <pthread.h>
#include <queue>
#include <string>

typedef struct _task_arg{
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

        // Default constructor (initialize lock)
        TaskQueue(){
            /* pthread_init_lock(&lock, nullptr); */
        }

        // Deconstructor, nothing special
        ~TaskQueue(){}

        /* void push(Task); */

    private:
        std::queue<Task> inbox;
        std::queue<Task> outbox;
        pthread_mutex_t  lock;
};

#endif

