//
// Created by Trevor Barron John Hritz
//

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <alloca.h>
#include "sem.h"

#define forever while(true)

//declare variables
int* arr;
int arr_size = 3;
sem_t block_parent;
sem_t block_child;

void child()
{
    //forever
    forever
    {
        //invoke block_child
        P(&block_child);

        //increment element in arr at the position indicated by the child's thread number
        //relative to the parent
        arr[(Curr_Thread->thread_id) - 1]++;

        //release block_parent
        V(&block_parent);
    }
    //endforever
}

void print()
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
    //initialize arr to size arr_size and containing all 0s
    arr = realloc(arr, arr_size);
    memset(arr, 0, arr_size);

    //create 3 children running child function
    for(int i = 0; i < 3; i++)
    {
        start_thread(&child);
    }

    //forever
    forever
    {
        //invoke block_parent 3 times
        for(int i = 0; i < arr_size; i++)
        {
            P(&block_parent);
        }

        //print array contents
        print(3);

        //release block_child 3 times
        for(int i = 0; i < arr_size; i++)
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

    //EXTENSION: convert argv[1] (the number of threads) to an int and store as arr_size
    //arr_size = atoi(argv[1]);

    //allocate the array
    arr = malloc(arr_size * sizeof(int));

    //initialize semaphores
    InitSem(&block_parent,0);
    InitSem(&block_child, 0);

    //create parent thread
    start_thread(&parent);

    //start the first thread
    run();
}