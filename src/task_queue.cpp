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

Worker::Worker(unsigned _MAX_THREADS, TaskQueue *_queue):
        MAX_THREADS(_MAX_THREADS)
      , active_threads(0)
      , threads(new pthread_t[MAX_THREADS])
      , args(new task_arg_t[MAX_THREADS])
      , queue(_queue){
}

Worker::~Worker(){
    delete [] threads; delete [] args;}

void Worker::handle_task_ready(){
    while(active_threads >= MAX_THREADS);

}

