#ifndef QUEUE_H
#define QUEUE_H

#ifdef _WIN32
#  include <windows.h>
#else
#  include <sys/types.h>
#endif

struct element
{
  size_t id;
};

void queue_init(void);

void enqueue(struct element);

struct element dequeue(void);

void monitor(void);

#endif
