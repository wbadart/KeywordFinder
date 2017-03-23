#include "task_queue.hpp"

TaskQueue::TaskQueue(size_t nthreads){
    NUM_THREADS = nthreads;
}

TaskQueue::~TaskQueue(){}

void TaskQueue::push(Task* t){
    q.push(t);
}

Task* TaskQueue::pop(){
    Task* ret = q.back();
    q.pop();
    return ret;
}
