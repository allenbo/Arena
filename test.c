#include <stdio.h>
#include <sys/time.h>
#include "arena.h"

#include <stdlib.h>

static const int MAX_SIZE = 12345;
static const int MIN_SIZE = 6;
static const int NUM = 100000;
static int sizes[NUM];

void init() {
  for(int i = 0; i < NUM; i ++ ) {
    sizes[i] = rand() / (MAX_SIZE - MIN_SIZE) + MIN_SIZE;
  }
}

typedef void(*MallocFunc) (void);

float time_diff(struct timeval* start, struct timeval* end) {
  return (end->tv_sec - start->tv_sec)  + (end->tv_usec - start->tv_usec) / 1000000.0;
}

void timeit(MallocFunc func, const char* name)  {
  struct timeval start;
  struct timeval end;
  gettimeofday(&start, NULL);
  func();
  gettimeofday(&end, NULL);
  float diff = time_diff(&start, &end);
  printf("%s on %d malloc and free: %f\n", name, NUM, diff);
}

void builtin_malloc() {
  char* malloced_pointers[NUM] = {0};
  for(int i = 0; i < NUM; i ++) {
    malloced_pointers[i] = (char*) malloc(sizes[i]);
    if (i % 3 == 0 && i != 0) {
      free(malloced_pointers[i-1]);
      malloced_pointers[i-1] = NULL;
    }
  }
  for(int i = 0; i < NUM ; i ++) {
    if (malloced_pointers[i] != NULL) {
      free(malloced_pointers[i]);
    }
  }
}

void arena_malloc() {
  Arena * arena = arena_New();
  for(int i = 0; i < NUM; i ++) {
    char* pointer = (char*) arena_Malloc(arena, sizes[i]); 
  }
  arena_Free(arena);
}

int main()  {
  init();
  timeit(&builtin_malloc, "builtin");
  timeit(&arena_malloc, "arena");
  return 0;
}
