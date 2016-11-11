//
// Created by Trevor Barron John Hritz
//

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <alloca.h>
#include "sem.h"
#include "threads.h"

#define forever for(;;)

//declare variables
int arr[3];
sem_t block_parent;
sem_t block_child;

void child(int num)
{
    //forever
    forever
    {
        //invoke block_child
        P(&block_child);

        //increment array[num]
        arr[num]++;

        //release block_parent
        V(&block_parent);
    }
    //endforever
}

void print(int arr_size)
{
    printf("[");

    //print all elements except the last one
    for(int i; i < (arr_size - 1); i++)
    {
        printf("%d, ", arr[i]);
    }

    //print last element
    printf("%d", arr[arr_size - 1]);

    printf("]");
}

void parent()
{
    //initialize arr to size N and containing all 0s
    realloc(arr, 3);
    memset(arr, 0, 3);

    //create 3 children running child function
    for(int i = 0; i < 3; i++)
    {
        start_thread(&child(i));
    }

    //forever
    forever
    {
        //invoke block_parent 3 times
        for(int i = 0; i < 3; i++)
        {
            P(&block_parent);
        }

        //print array contents
        print(3);

        //release block_child 3 times
        for(int i = 0; i < 3; i++)
        {
            V(&block_child);
        }
    }
    //endforever
}

int main(int argc, const char* argv[])
{
    //define ReadyQ from threads.h
    ReadyQ = newQueue();

    //EXTENSION: convert argv[1] (the number of threads) to an int and store

    //initialize semaphores
    InitSem(&block_parent,0);
    InitSem(&block_child, 0);

    //create parent thread
    start_thread(&parent);

    //start the first thread
    run();
}