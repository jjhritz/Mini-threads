#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "threads.h"
#include "q.h"

int f1 = 0;
int f2 = 0;
int f3 = 0;

void func1() {
  while (true) {
    sleep(1.0);
    printf ("Hello from func1 %d\n", f1);
    f1++;
    yield();
  }
}

void func2() {
  while (true) {
    sleep(1.0);
    printf ("Hello from func2 %d\n", f2);
    f2++;
    yield();
  }
}

void func3() {
  while (true) {
    sleep(1.0);
    printf ("Hello from func3 %d\n", f3);
    f3++;
    yield();
  }
}

int main() {
  init_readyq();
  start_thread(&func1);
  start_thread(&func2);
  start_thread(&func3);
  run();

  return 0;
}
