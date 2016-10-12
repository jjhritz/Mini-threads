/*
 * Trevor Barron & John Hritz
 * CSE 330 Project 2
 * 10/11/16
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "threads.h"
#include "q.h"

int global = 0;

void func1() {
  int local = 0;
  while (true) {
    sleep(1.0);
    printf ("Hello from func1 local %d, global %d\n", local, global);
    global++;
    local++;
    yield();
  }
}

void func2() {
  int local = 0;
  while (true) {
    sleep(1.0);
    printf ("Hello from func2 local %d, global %d\n", local, global);
    global++;
    local++;
    yield();
  }
}

void func3() {
  int local = 0;
  while (true) {
    sleep(1.0);
    printf ("Hello from func3 local %d, global %d\n", local, global);
    global++;
    local++;
    yield();
  }
}

int main() {
  ReadyQ = newQueue();
  Curr_Thread = NewItem();

  start_thread(&func1);
  start_thread(&func2);
  start_thread(&func3);

  run();

  return 0;
}
