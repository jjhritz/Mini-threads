/*
 * Trevor Barron & John Hritz
 * CSE 330 Project 3
 * 10/24/16
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "threads.h"
#include "q.h"
#include "sem.h"

#define SIZE 10

sem_t full;
sem_t empty;

int data[SIZE] = { 0 };
int in = 0, out = 0;

void prod() {
  int local = 0;
  while (true) {
    P(&full);

    printf ("Adding value %d to data index %d\n", local, in);
    data[in] = local;
    local++;
    in = (in+1) % SIZE;
    sleep(1.0);

    V(&empty);
  }
}

void cons() {
  while (true) {
    P(&empty);

    int val = data[out];
    printf ("Retrieved value %d from data\n", val);
    out = (out+1) % SIZE;

    V(&full);
  }
}

int main() {
  InitSem(&full, SIZE);
  InitSem(&empty, 0);

  ReadyQ = newQueue();
  Curr_Thread = NewItem();

  /*
   * Usually you would need mutexes around the critical sections
   * since you can have a case where the buffer is both not full
   * and not empty and could end up reading and writing simultaneously.
   * But here everything is single threaded so we have no problem.
   */
  start_thread(&prod);
  start_thread(&prod);
  start_thread(&cons);
  start_thread(&cons);

  run();

  return 0;
}
