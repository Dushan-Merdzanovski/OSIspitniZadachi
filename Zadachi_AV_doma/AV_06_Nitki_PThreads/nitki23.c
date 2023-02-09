#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define NUM_THREADS 10
int niza[1000];
int maxg[10];

void *generiraj(void *t)
{
  int i;
  long tid = (long)t;
  pthread_t ttid = pthread_self();
  srand(time(NULL));
  printf("Thread %ld start generating\n", tid);
  for (i = tid * 100; i < tid * 100 + 100; i++)
  {
    niza[i] = rand() % 10000;
  }
  pthread_exit((void *)t);
}

void *prebaraj(void *t)
{
  int i, rc = 1, cycles = 0;
  long tid = (long)t;
  void *status;
  printf("Thread %ld start searching\n", tid);
  int max = niza[tid * 100];
  for (i = tid * 100; i < tid * 100 + 100; i++)
  {
    if (niza[i] > max)
    {
      max = niza[i];
    }
  }
  maxg[tid] = max;
  pthread_exit((void *)t);
}

int main(int argc, char *argv[])
{
  pthread_t threads[10];
  int rc1, rc2;
  long t;
  void *status;
  for (t = 0; t < NUM_THREADS; t++)
  {
    printf("Main: creating thread %ld\n", t);
    rc1 = pthread_create(&threads[t], NULL, generiraj, (void *)t);
    if (rc1)
    {
      printf("ERROR; return code from pthread_create() is %d\n", rc1);
      exit(-1);
    }
  }
  for (t = 0; t < NUM_THREADS; t++)
  {
    rc1 = pthread_join(threads[t], &status);
    if (rc1)
    {
      printf("ERROR; return code from pthread_join() is %d\n", rc1);
      exit(-1);
    }
    printf("Main: completed join with thread %ld having a status of %ld\n", t, (long)status);
  }
  for (t = 0; t < NUM_THREADS; t++)
  {
    printf("Main: creating thread %ld\n", t);
    rc1 = pthread_create(&threads[t], NULL, prebaraj, (void *)t);
    if (rc1)
    {
      printf("ERROR; return code from pthread_create() is %d\n", rc1);
      exit(-1);
    }
  }
  for (t = 0; t < NUM_THREADS; t++)
  {
    rc1 = pthread_join(threads[t], &status);
    if (rc1)
    {
      printf("ERROR; return code from pthread_join() is %d\n", rc1);
      exit(-1);
    }
    printf("Main: completed join with thread %ld having a status of %ld\n", t, (long)status);
  }

  int max = maxg[0];
  for (t = 0; t < 10; t++)
  {
    if (maxg[t] > max)
    {
      max = maxg[t];
    }
  }
  printf("Najgolemiot element e %d\n", max);
  pthread_exit(NULL);
}