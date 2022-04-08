#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() // hello.c
{
    printf("hello! pid = %d parent = %d\n", getpid(), getppid());
    return 0;
}
