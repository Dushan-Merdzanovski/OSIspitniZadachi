#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
  pid_t dete;
  int fd, i, j;
  int *p;
  dete = fork();
  if (dete == 0)
  {
    // proces 1
    if ((fd = open(argv[1], O_RDWR | O_CREAT, 00666)) == -1)
    {
      printf("neuspesno otvoranje na datotekata\n");
      return 0;
    }
    // kreiranje na memorija za novo-kreiraniot file
    if (ftruncate(fd, 1000 * (sizeof(int))) == -1)
    {
      printf("neuspesno proshiruvanje na memorijata\n");
      return 0;
    }
    p = mmap(NULL, 1000 * (sizeof(int)), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED)
    {
      printf("neuspesno mapiranje na memorijata\n");
      return 0;
    }

    for (i = 2, j = 0; i <= 2000; i += 2, j++)
    {
      p[j] = i;
    }
    munmap(p, 1000 * (sizeof(int)));
  }
  else
  {
    wait(NULL);
    if ((fd = open(argv[1], O_RDWR)) == -1)
    {
      printf("neuspesno otvoranje na datotekata");
      return 0;
    }
    p = mmap(NULL, 1000 * (sizeof(int)), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED)
    {
      printf("neuspesno mapiranje na memorijata");
      return 0;
    }
    for (i = 0; i < 1000; i++)
    {
      printf("%d\t", p[i]);
    }
    munmap(p, 1000 * (sizeof(int)));
    // proces 2
  }
  return 0;
}