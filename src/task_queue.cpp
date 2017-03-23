/**
 * task_queue.cpp
 *
 * Implementation of threading and working.
 *
 * Badart, Cat
 * Badart, Will
 * created: MAR 2017
 */

#include "task_queue.hpp"

void *thread_function_proxy(void *args);

TaskQueue::TaskQueue(unsigned _MAX_THREADS):
        MAX_THREADS(_MAX_THREADS)
      , active_threads(0)
      , threads(new pthread_t[MAX_THREADS])
      , args(new task_arg_t[MAX_THREADS]){
    pthread_cond_init(&cond, nullptr);
    pthread_mutex_init(&mux, nullptr);
}

TaskQueue::~TaskQueue(){
    delete [] threads; delete [] args;
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mux);
}

void TaskQueue::push(Task *t){
    // Don't know yet how to get the index of the first available
    //     thread (put in conditional var?). Will become offset
    args[0/*offset*/].target = t;
    pthread_create(threads /* plus some calculated offset */
                 , nullptr
                 , thread_function_proxy
                 , args /* plus some calculated offset */);
}

void TaskQueue::pipe_to(TaskQueue *_next){
    next = _next; }

void *thread_function_proxy(void* args){
    task_arg_t *cast_args = (task_arg_t*)args;
    cast_args->target->exec(cast_args);
    return nullptr;
}

