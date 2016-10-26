//
// Created by student on 10/23/16.
//

#include "q.h"

#ifndef CSE330PROJECT_SEM_H
#define CSE330PROJECT_SEM_H

//structure to define semaphores
typedef struct sem_t
{
    int val;        //value of the semaphore
    TCB_t* queue;   //queue of threads waiting on this semaphore
} sem_t;


// Initializes the value field with the specified value.
void InitSem(sem_t* sem, int val)
{
    //set the value of the parameter semaphore to the parameter value
    sem->val = val;
    sem->queue = newQueue();
}

//decrements the semaphore, and if the value is less than zero
//then blocks the thread in the queue associated with the semaphore
void P(sem_t* sem)
{
    //decrement the semaphore
    sem->val--;

    // if the value is LTE zero, block the thread
    if(sem->val < 0)
    {
        //add the current thread to the semaphore queue
        AddQueue(sem->queue, Curr_Thread);

        //store the current thread for context switch
        struct TCB_t* Prev_Thread = Curr_Thread;

        //get the next thread from the ready queue
        Curr_Thread = DelQueue(ReadyQ);

        //swap context to next thread
        swapcontext(&(Prev_Thread->context), &(Curr_Thread->context));
    }
}

//Increments the semaphore, and if the value is 0 or negative,
//then takes a PCB out of the semaphore queue and puts it into the ReadyQ queue.
void V(sem_t* sem)
{
    //increment the semaphore
    sem->val++;

    //if value is less than or equal to zero, add the next thread to the ready queue
    if(sem->val <= 0)
    {
        AddQueue(ReadyQ, DelQueue(sem->queue));
    }
    //yield to the next thread
    yield();
}

#endif //CSE330PROJECT_SEM_H
