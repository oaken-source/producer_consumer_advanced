
#include "queue.h"

#include "main.h"

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

volatile struct element queue[QUEUE_CAPACITY] = { 0 };
size_t head_r = 0;
size_t head_w = 0;
volatile size_t queue_filled = 0;
volatile size_t queue_empty = QUEUE_CAPACITY;

void
queue_init (void)
{
  // noop
}

void
enqueue (struct element e)
{
  while (queue_empty == 0);

  queue[head_w] = e;
  head_w = (head_w + 1) % QUEUE_CAPACITY;
  queue_filled++;

  queue_empty--;
}

struct element
dequeue (void)
{
  while (queue_filled == 0);

  struct element e = queue[head_r];
  head_r = (head_r + 1) % QUEUE_CAPACITY;
  queue_empty++;

  queue_filled--;

  return e;
}

void
monitor (void)
{
  while (1)
    {
      printf("filled %zu; avail: %zu; current: %zu\n", queue_filled, queue_empty, queue[head_r].id);

      usleep(MONITOR_INTERVAL);
    }
}
