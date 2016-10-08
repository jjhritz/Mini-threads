/*
 * Body files including this header must also use the following includes:
 * #include <stdbool.h>
 * #include <stdlib.h>
 * #include <stdio.h>
 *
 * Body files including this header must be compiled using C99.  Add -std=c99 to gcc options
 */

#ifndef CSE330P1_Q_H
#define CSE330P1_Q_H


struct item
{
    int payload;
    struct item* next;
    struct item* prev;
};

//This function is called when a system call fails. It displays a message about the error on stderr
//(#include <stdio.h>in test cases and other body files)
void error(const char *msg)
{
    //print error message
    perror(msg);
    //teminate the program (not sure if needed)
    //exit(0);
}

//tests if queue pointed to by head is empty.  Returns true/false.  #include <stdbool.h> in test cases and other body files. Compile in C99 mode.
bool isEmpty(struct item* head)
{
    //create boolean flag to return with status of queue
    bool isEmpty = false;

    //if head->next AND head->prev both point to head, the queue is empty.
    if(head->next == head
        && head->prev == head)
    {
        isEmpty = true;
    }

    //return isEmpty
    return isEmpty;
}

// returns a pointer to a new q-element, uses memory allocation
struct item* NewItem()
{
    //create item variable
    struct item* new_item;
    //malloc item (#include <stdlib.h> in test cases and other body files)
    new_item = malloc(sizeof(struct item));
    //return item
    return new_item;
}

// creates a empty queue, consisting of one dummy element, returns the head pointer.
struct item* newQueue()
{
    //create head variable
    struct item* head;
    //malloc head (#include <stdlib.h> in test cases and other body files)
    head = malloc(sizeof(struct item));
    //make head->next point at head
    head->next = head;
    //make head->prev point at head
    head->prev = head;
    //return head
    return head;
}

// adds a queue item, pointed to by “item”, to the queue pointed to by head.
void AddQueue(struct item* head, struct item* new_item)
{
    /*
     * h -> h ; h <- h
     * h -> new1 -> h; new1 <- h <- new1
     * h -> new1 -> new2 -> h; new2 <- h <- new1 <- new2
     */
    //create pointer at end of list
    struct item* last = head->prev;
    //make last element->next point to new_item
    last->next = new_item;
    //make new_item->prev point to last element
    new_item->prev = last;
    //make new_item->next point to head
    new_item->next = head;

    //make heads prev item new_item
    head->prev = new_item;
}

// deletes first item in queue and returns a pointer to the deleted item. If the queue is already empty, flag error.
// Returns NULL if queue is empty
struct item* DelQueue(struct item* head)
{
    //create variable that will point to popped item
    struct item* popped_item = NULL;

    //if head is empty, print error
    if(isEmpty(head))
    {
        error("ERROR: Empty queue.");
    }
    //else, pop the first element
    else
    {
        //make popped_item point to the first element in the queue
        popped_item = head->next;
        //Advance second element in queue to first position
        head->next = head->next->next;
        //link back new first element to head
        head->next->prev = head;
    }
    //end if

    //return popped_item
    return popped_item;
}

#endif //CSE330P1_Q_H
