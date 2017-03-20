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

template<typename T>
class Task{

    public:
        virtual void exec(std::string);
    private:
};

template<typename in_t, typename out_t>
class TaskQueue{

    public:

        // Default constructor (initialize lock)
        TaskQueue(){
            /* pthread_init_lock(&lock, nullptr); */
        }

        // Deconstructor, nothing special
        ~TaskQueue(){}

        void push(Task<in_t>);

    private:
        std::queue<in_t>  inbox;
        std::queue<out_t> outbox;
        pthread_mutex_t   lock;
};

#endif

