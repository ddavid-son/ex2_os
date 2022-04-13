#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    FILE *of = fopen(argv[argc - 1], "w");
    fclose(of);
    for (int i = 1; i < argc - 1; i++)
    {
        if (fork() == 0)
        {
            close(0);
            open(argv[i], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

            close(1);
            open(argv[argc - 1], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

            char *newargv[] = {"", argv[argc - 1], NULL};
            execve("merger", newargv, NULL);
        }
        sleep(1);
    }
    return 0;
}