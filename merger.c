#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "stdbool.h"
#include <unistd.h>

#define STDIN_NAME "standard input"
#define STDOUT_NAME "standard output"

typedef struct student
{
    char name[11];
    int grades[10];
    int grades_num;
} student;

student students[100];
int studs_num = 0;
int arr_size = 16;

double calc_avg();
void sort_grades();
void print_data_summary();
void get_stud_data_stdin();
bool stud_exists(char *name);
void create_new_stud(char *name);
void add_grades(char *stud_data);
int compare(const void *a, const void *b);
void get_stud_data(int files_num, char *argv[]);
void report_data_summary(int num_stud, double avg);
void report_input_file(const char *file_name, int num_stud);

int main(int argc, char *argv[])
{
    get_stud_data_stdin();
    if (argc == 2)
    {
        get_stud_data(argc, argv);
    }

    sort_grades();
    print_data_summary();
    report_data_summary(studs_num, calc_avg());

    return 0;
}

void print_data_summary()
{
    for (int i = 0; i < studs_num; i++)
    {
        printf("%s ", students[i].name);
        for (int j = 0; j < students[i].grades_num; j++)
        {
            printf("%d ", students[i].grades[j]);
        }
        printf("\n");
    }
    fflush(stdin);
}

void get_stud_data_stdin()
{
    char line[81];
    int stud_in_file = 0;

    while (fgets(line, 81, stdin) != NULL)
    {
        stud_in_file++;
        add_grades(line);
    }
    report_input_file(STDIN_NAME, stud_in_file);
}

double calc_avg()
{
    int sum = 0;
    int grades_num = 0;
    for (int i = 0; i < studs_num; i++)
    {
        for (int j = 0; j < students[i].grades_num; j++)
        {
            sum += students[i].grades[j];
            grades_num++;
        }
    }
    return (double)sum / grades_num;
}

void sort_grades()
{
    for (int i = 0; i < studs_num; i++)
    {
        qsort(students[i].grades, students[i].grades_num, sizeof(int), compare);
    }
}

int compare(const void *a, const void *b)
{
    return *(int *)b - *(int *)a;
}

void get_stud_data(int file_num, char *argv[])
{
    int stud_in_file = 0;
    char line[81];
    for (int i = 1; i < file_num; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("Error Reading File\n");
            exit(1);
        }
        while (fgets(line, 81, fp) != NULL)
        {
            if (line[0] == '\n')
            {
                continue;
            }
            else
            {
                stud_in_file++;
                add_grades(line);
            }
        }
        fclose(fp);
        report_input_file(argv[i], stud_in_file);
        stud_in_file = 0;
    }
}

void add_grades(char *stud_data)
{
    char *name = strtok(stud_data, " ");
    char *grades;
    if (!stud_exists(name))
    {
        create_new_stud(name);
    }

    for (int i = 0; i < studs_num; i++)
    {
        if (strcmp(students[i].name, name) == 0)
        {
            grades = strtok(NULL, " ");
            while (grades != NULL && (*grades) != '\n' && (*grades) != '\r')
            {
                students[i].grades[students[i].grades_num] = atoi(grades);
                grades = strtok(NULL, " ");
                students[i].grades_num++;
            }

            return;
        }
    }
}

void create_new_stud(char *name)
{
    student stud;
    strcpy(stud.name, name);
    stud.grades_num = 0;
    students[studs_num++] = stud;
}

bool stud_exists(char *name)
{
    for (int i = 0; i < studs_num; i++)
    {
        if (strcmp(students[i].name, name) == 0)
        {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------- Tzvi report format ----------------------------------------------------- //
void report_input_file(const char *file_name, int num_stud)
{
    fprintf(stderr, "process: %d file: %s number of students: %d\n",
            getpid(), file_name, num_stud);
}

void report_data_summary(int num_stud, double avg)
{
    fprintf(stderr, "process: %d data summary - number of students:"
                    " %d grade average: %.2f\n",
            getpid(), num_stud, avg);
}
// ---------------------------------------------- Tzvi report format ----------------------------------------------------- //
