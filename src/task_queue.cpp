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

// Initialize static members
pthread_cond_t  TaskQueue::cond;
pthread_mutex_t TaskQueue::mux;

TaskQueue::TaskQueue(unsigned _MAX_THREADS):
        MAX_THREADS(_MAX_THREADS)
      , nthreads(0)
      , threads(new pthread_t[MAX_THREADS])
      , args(new task_arg_t[MAX_THREADS])
      , next(nullptr){
    pthread_cond_init(&cond, nullptr);
    pthread_mutex_init(&mux, nullptr);
}

TaskQueue::~TaskQueue(){
    delete [] threads; delete [] args;
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mux);
}

void TaskQueue::pipe_to(TaskQueue *_next){
    next = _next; }

bool TaskQueue::done(){
    return queue.empty(); }

void *TaskQueue::thread_function_proxy(void* args){
    task_arg_t *cast_args = (task_arg_t*)args;
    cast_args->target->exec(cast_args);
    return nullptr;
}

