#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t id1;
    pid_t id2;
    pid_t id3;
    pid_t tatko = getpid();
    pid_t dete;
    int chekaj = 3;
    printf("Moeto ID e %ld\n", (long)getpid());
    printf("Tatko mi ima ID %ld\n", (long)getppid());
    id1 = fork();
    if (id1 == 0)
        printf("Jas sum prvo dete proces so ID %ld i ParentID %ld\n", (long)getpid(), (long)tatko);
    else
    {
        printf("Jas sum tatkoto so proces ID %ld i ParentID%ld\n", (long)getpid(), (long)getppid());
        id2 = fork();
        if (id2 == 0)
            printf("Jas sum vtoro dete proces so ID %ld i parentID %ld\n", (long)getpid(), (long)tatko);
        else
        {
            printf("Jas sum tatkoto so proces ID %ld i ParentID %ld\n", (long)getpid(), (long)getppid());
        
            id3 = fork();
            if (id3 == 0)
                printf("Jas sum treto dete proces so ID %ld i parentID%ld\n", (long)getpid(), (long)tatko);
            else
            {
                printf("Jas sum tatkoto so proces ID %ld i parentID %ld\n", (long)getpid(), (long)getppid());
                while (chekaj)
                {
                    if ((dete = wait(NULL)) != -1)
                    {
                        printf("docekav dete so proces id %ld\n", (long)dete);
                        chekaj--;
                    }
                }
            }
        }
    }

    return 0;
}
