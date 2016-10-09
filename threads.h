/*
 * #include <alloca.h>
 */

#ifndef CSE330PROJECT_THREADS_H
#define CSE330PROJECT_THREADS_H

#include "q.h"
#include <stdio.h>

struct TCB_t* ReadyQ;
struct TCB_t* Curr_Thread;

void init_readyq() {
  ReadyQ = newQueue();
}

void start_thread(void (*function)(void))
{
    //allocate a stack (via malloc) of a certain size (choose 8192)
    void* stack = malloc(8192);
    //allocate a TCB (via malloc)
    TCB_t *TCB = malloc(sizeof(TCB_t));
    //call init_TCB with appropriate arguments
    init_TCB (TCB, function, stack, 8192);
    //call addQ to add this TCB into the “ReadyQ” which is a global header pointer
    AddQueue(ReadyQ, TCB);
}

void print_queue() {
  while (!isEmpty(ReadyQ)) {
    TCB_t *t = DelQueue(ReadyQ);
    printf("TID = %d\n", t->thread_id);
  }
}

void run()
{
    Curr_Thread = DelQueue(ReadyQ);
    ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, &(Curr_Thread->context));  // start the first thread
}

void yield() // similar to run
{
    //add the current thread to the queue
    AddQueue(ReadyQ, Curr_Thread);
    //store the current thread
    struct TCB_t* Prev_Thread = Curr_Thread;
    //get the next thread in the queue
    Curr_Thread = DelQueue(ReadyQ);
    //swap the context, from Prev_Thread to the thread pointed to Curr_Thread
    ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, &(Curr_Thread->context));  // start the next thread
    // end pseudo code
}

void print_thread_id(struct TCB_t* thread)
{
    printf("Thread ID: %d/n", thread->thread_id);
}

#endif //CSE330PROJECT_THREADS_H
