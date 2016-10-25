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

int global = 0;
sem_t mutex;

void func1() {
  int local = 0;
  while (true) {
    P(&mutex);
    sleep(1.0);
    printf ("Hello from func1 local %d, global %d\n", local, global);
    global++;
    local++;
    V(&mutex);
  }
}

void func2() {
  int local = 0;
  while (true) {
    P(&mutex);
    sleep(1.0);
    printf ("Hello from func2 local %d, global %d\n", local, global);
    global++;
    local++;
    V(&mutex);
  }
}

int main() {
  InitSem(&mutex, 1);

  ReadyQ = newQueue();
  Curr_Thread = NewItem();

  start_thread(&func1);
  start_thread(&func2);

  run();

  return 0;
}
