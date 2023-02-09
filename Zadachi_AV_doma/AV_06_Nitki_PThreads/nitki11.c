/* kreira 5 nitki i pthread_join */

#include <stdio.h>
#include <pthread.h>

void *funk(void *t)
{
  int i = *((int *)t);

  printf("Jas sum nitka so id %d\n", i + 1);

  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

  int i;
  pthread_t nitki[5];

  for (i = 0; i < 5; i++)
  {
    int rc = pthread_create(&nitki[i], NULL, funk, (void *)&i);
    printf("rc = %d ", rc);
  }
  for (i = 0; i < 5; i++)
  {
    pthread_join(nitki[i], NULL);
    printf("pristigna nitka %d\n", i);
  }
  return 0;
}