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
    char *argv[2] = {"./hello", NULL};
    printf("parent pid = %d starting\n", getpid()); // parent pid is 100
    int ret;
    fork();
    fork();
    ret = wait(NULL);
    if (ret < 0)
        sleep(1);
    if (ret > 100)
        execve(argv[0], argv, NULL);
    else
        printf("byebye pid = %d parent = %d\n", getpid(), getppid());
    return 0;
}