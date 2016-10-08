#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#include "q.h"


void print_queue(struct item* head) {
  if (head == NULL)
    return;
  struct item* cur = head;
  printf("%d ", cur->payload);
  cur = cur->next;
  while (cur != head) {
    printf("%d ", cur->payload);
    cur = cur->next;
  }
  printf("\n");
}


int rand_in_range(int n) {
  return rand() % n;
}


// get the size of the queue
int size(struct item* q) {
  if (q == NULL) {
    return 0;
  }
  int s = 0;
  struct item* cur = q->next;
  while (cur != q) {
    s++;
    cur = cur->next;
  }
  return s;
}


void check_size(struct item* q, int expected) {
  assert (size(q) == expected);
  printf("Size check passed!\n");
}

struct item* make_simple_queue(int n) {
  struct item* q = newQueue();
  q->payload = -1;

  int i;
  for (i = 0; i < n; ++i) {
    struct item* a = NewItem();
    a->payload = i+1;
    AddQueue(q, a);
  }

  // struct item* a = NewItem();
  // a->payload = 1;
  // AddQueue(q, a);
  //
  // struct item* b = NewItem();
  // b->payload = 2;
  // AddQueue(q, b);
  //
  // struct item* c = NewItem();
  // c->payload = 3;
  // AddQueue(q, c);

  return q;
}


struct item* make_random_queue(size) {
  // Pass -1 to make random length
  int range = 100;
  struct item* q = newQueue();
  q->payload = -1; // dummy element

  int n = size;
  if (n == -1) {
    // n between 20 and 30 though not uniformly
    n = rand() % 10 + 20;
  }
  int i;
  for (i = 0; i < n; ++i) {
    struct item* a = NewItem();
    a->payload = rand_in_range(range); ///rand();
    AddQueue(q, a);
  }
  return q;
}


void add_random_n_elements(struct item* head, int n) {
  int range = 100;
  int i;
  for (i = 0; i < n; ++i) {
    struct item* a = NewItem();
    a->payload = rand_in_range(range);
    AddQueue(head, a);
  }
}


void delete_and_print(struct item* head) {
  struct item* pop = DelQueue(head);
  if (pop != NULL) {
    printf("%d\n", pop->payload);
    free(pop);
  } else {
    printf("delete failed, queue empty\n");
  }
}


void delete_entire_queue(struct item* head) {
  struct item* pop;
  while ((pop = DelQueue(head)) != NULL) {
    free(pop);
  }
  // Don't free head
}

void free_queue(struct item* head) {
  delete_entire_queue(head);
  free(head);
}

void single_queue_test() {
  printf("single_queue_test\n");
  struct item* q1 = make_simple_queue(3);

  printf("q:\n");
  print_queue(q1);
  check_size(q1, 3);

  printf("deleting q:\n");
  delete_entire_queue(q1);
  check_size(q1, 0);

  printf("trying another delete\n");
  delete_and_print(q1);
  check_size(q1, 0);

  printf("q:\n");
  print_queue(q1);

  free_queue(q1);
  printf("\n\n");
}

void multiple_queues_test() {
  printf("multiple_queues_test\n");
  struct item* q1 = make_simple_queue(3);
  struct item* q2 = make_random_queue(3);

  printf("q1:\n");
  print_queue(q1);
  check_size(q1, 3);
  printf("q2:\n");
  print_queue(q2);
  check_size(q2, 3);

  printf("deleting q1:\n");
  delete_and_print(q1);
  check_size(q1, 2);
  delete_and_print(q1);
  check_size(q1, 1);
  delete_and_print(q1);
  check_size(q1, 0);
  printf("deleting q2:\n");
  delete_and_print(q2);
  check_size(q2, 2);
  delete_and_print(q2);
  check_size(q2, 1);
  delete_and_print(q2);
  check_size(q2, 0);

  add_random_n_elements(q1, 3);
  check_size(q1, 3);
  add_random_n_elements(q2, 3);
  check_size(q2, 3);

  printf("q1:\n");
  print_queue(q1);
  printf("q2:\n");
  print_queue(q2);

  printf("deleting q1:\n");
  delete_and_print(q1);
  delete_and_print(q1);
  delete_and_print(q1);
  printf("deleting q2:\n");
  delete_and_print(q2);
  delete_and_print(q2);
  delete_and_print(q2);

  printf("trying too many deletes\n");
  delete_and_print(q1);
  delete_and_print(q2);

  printf("q1:\n");
  print_queue(q1);
  printf("q2:\n");
  print_queue(q2);

  check_size(q1, 0);
  check_size(q2, 0);

  free_queue(q1);
  free_queue(q2);
  printf("\n\n");
}


int main() {
  srand((unsigned int)time(NULL));

  single_queue_test();
  printf("\n");
  multiple_queues_test();

  return 0;
}
