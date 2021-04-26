
#include "producer.h"
#include "consumer.h"
#include "queue.h"
#include "util.h"
#include "thread_helper.h"

#include <stdlib.h>
#include <stdio.h>

int
main (int argc, char *argv[])
{
  int thread_count;
  int *thread_args;

  thread_helper_t *threads;

  int i;

  if (argc < 2)
    {
      fprintf(stderr, "Usage: %s <thread_count>\n", argv[0]);
      return 1;
    }

  thread_count = atoi(argv[1]);

  if (thread_count < 2)
    {
      fprintf(stderr, "No valid thread number provided.\n");
      return 1;
    }

  thread_args = malloc(sizeof(*thread_args) * thread_count);
  if (!thread_args)
    {
      perror("malloc");
      return 2;
    }

  threads = malloc(sizeof(*threads) * (thread_count - 1));
  if (!threads)
    {
      perror("malloc");
      return 2;
    }

  srand(time(NULL));

  // prepare the queue
  queue_init();

  // start producer and consumer threads
  for (i = 0; i < thread_count; ++i)
    {
      thread_args[i] = i;

      if (thread_helper_create(threads + i, (i & 1) ? &produce : &consume, thread_args + i) != 0)
        {
          perror("thread_helper_create");
          return 1;
        }

    }

  // monitor their progress
  monitor();
}
