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

        // Default constructor (initialize lock)
        TaskQueue(size_t); /* pthread_init_lock(&lock, nullptr); */

        // Deconstructor, nothing special
        ~TaskQueue();

        // Add task, broadcast task ready
        void push(std::string fname_or_url);

    private:
        /* std::queue<Task> inbox; */
        /* std::queue<Task> outbox; */
};

class Worker{

    public:

        // Constructor allocates threads and args
        Worker(unsigned _MAX_THREADS, TaskQueue *_queue);

        // Deconstructor taketh away
        ~Worker();

    private:

        // Handles task ready broadcast; waits until
        //   active_threads < MAX and then spawns thread for task
        void handle_task_ready();

        // Track active threads and max threads
        unsigned MAX_THREADS;
        unsigned active_threads;

        // Thread and argument arrays
        pthread_t  *threads;
        task_arg_t *args;

        // Queue to grab tasks from
        TaskQueue *queue;
};

#endif

