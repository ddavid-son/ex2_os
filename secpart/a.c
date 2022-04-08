#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    printf("my-pid = %d first process starting\n", getpid()); // parent pid is 100
    if (fork() || fork() == 0)
    {
        printf("my-pid = %d parent-pid = %d starting\n", getpid(), getppid());
    }
    if (getpid() != 100)
        sleep(1);
    printf("going to exit pid = %d, ppid = %d\n", getpid(), getppid());
    return 0;
}
