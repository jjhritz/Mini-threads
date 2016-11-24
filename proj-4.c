//
// Created by Trevor Barron John Hritz
//

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <alloca.h>
#include <unistd.h>
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
        // printf ("here tid %d\n", Curr_Thread ==NULL);
        // arr[0]++;
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
    for(int i = 0; i < (arr_size - 1); i++)
    {
        printf("%d, ", arr[i]);
    }

    //print last element
    printf("%d", arr[arr_size - 1]);
    printf("]\n");
}

void parent()
{
    //initialize arr to size arr_size and containing all 0s
    int bytes = arr_size * sizeof(int);
    arr = realloc(arr, bytes);
    memset(arr, 0, bytes);

    //create N children running child function
    for(int i = 0; i < arr_size; i++)
    {
        start_thread(&child);
    }

    //forever
    forever
    {
        //invoke block_parent N times
        for(int i = 0; i < arr_size; i++)
        {
            P(&block_parent);
        }

        //print array contents
        print();

        //release block_child N times
        for(int i = 0; i < arr_size; i++)
        {
            V(&block_child);
        }
        sleep(1);
    }
    //endforever
}

int main(int argc, const char* argv[])
{
    //define ReadyQ from threads.h
    ReadyQ = newQueue();

    //EXTENSION: convert argv[1] (the number of threads) to an int and store as arr_size
    if (argc > 1) {
        arr_size = atoi(argv[1]);
    }

    //allocate the array
    // We probably don't need the realloc if we compute the array size before malloc
    arr = malloc(arr_size * sizeof(int));

    //initialize semaphores
    InitSem(&block_parent, 0);
    InitSem(&block_child, arr_size);

    //create parent thread
    start_thread(&parent);

    //start the first thread
    run();
}
