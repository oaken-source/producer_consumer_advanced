
#include "producer.h"
#include "consumer.h"
#include "queue.h"

#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#  include <windows.h>
#elif (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
#  include <pthread.h>
#  include <sys/time.h>
#else
#  error Unsupported plattform
#endif

int
main (int argc, char *argv[])
{
  int thread_count;
  int *thread_args;
#ifdef _WIN32
  HANDLE    *threads;
#else
  pthread_t *threads;
#endif
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

#ifdef _WIN32
      threads[i] = CreateThread(NULL, 0, (i & 1) ? produce : consume, (void *)(thread_args + i), 0, NULL);
      if (threads[i] == NULL)
        {
          fprintf(stderr, "error: CreateThread (#%d)\n", GetLastError());
          return 3;
        }
#else
      if (pthread_create(&threads[i], NULL, (i & 1) ? produce : consume, (void *)(thread_args + i)) != 0)
        {
          perror("pthread_create");
          return 3;
        }
#endif

    }

  // monitor their progress
  monitor();
}
