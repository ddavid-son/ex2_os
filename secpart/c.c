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
    int fda, fdb, fda_dup, fdb_re_open;
    // open files for writing, create it if needed
    fda = open("X", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    fdb = open("Y", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);

    if (fork() == 0)
    {
        fda_dup = dup(fda);
        write(fda, "fda\n", 4);
        write(fda_dup, "dup\n", 4);
        exit(0);
    }
    if (fork() == 0)
    {
        fdb_re_open = open("Y", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
        write(fdb, "fdb\n", 4);
        write(fdb_re_open, "re-open\n", 8);
        exit(0);
    }
    close(fda);
    close(fdb);
    wait(NULL);
    wait(NULL);
}