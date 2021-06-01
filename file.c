/* Operating with files 

A few useful functions:
  - void rewind(FILE *ptr): sets the pointer to the
beginning of the file;
  - int getc(FILE *ptr): gets the next char as an
unsigned char and advances the pointer;
  - int putc(int char, FILE *ptr): writes char to
*ptr and returns EOF in case of an error and itself
if succesfull;
  - */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*void malc(char *data2[])
{
    int length = 10, size = 100;
    int i = 0;
    while (i < length)
    {
        data2[i] = (char*)malloc(size);
        i++;
    }
}

void read(FILE *ptr, int data1[], char *data2[], int *size)
{
    *size = 0;
    malc(data2);
    while (fscanf(ptr, "%d %s", &data1[*size], data2[*size]) == 2)
    {
        printf("Read: %d, %s\n", data1[*size], *(data2[*size]));
        (*size)++;
    }
}*/

double mean(int data[], int size)
{
    int i = 0;
    double sum = 0.0;
    for (i; i < size; i++)
        sum += data[i];
    return sum / size;
}

void print_ints(int data[], int size)
{
    int i = 0;

    for (i; i < size; i++)
        printf("%d\t", data[i]);
}

void print_strs(char data[][10], int size)
{
    int i = 0;

    for (i; i < size; i++)
        printf("%s\t", data[i]);
}

int main(void)
{
    FILE *ptr;
    int ints[3], size = 0, i = 0, intg;
    char strings[3][10];
    char string[10];
    double average;

    ptr = fopen("data.txt", "r");
    if (ptr == NULL)
    {
        printf("No such file or directory");
        return 1;
    }

    while (fscanf(ptr, "%d %s\n", &intg, string) == 2)
    {
        ints[i] = intg;
        strcpy(strings[i++], string);
        printf("Int: %d, Str: %s\n", i, string);
    }
    print_ints(ints, i);
    print_strs(strings, i);

    /*printf("Loaded\n");
    read(ptr, data1, data2, &size);
    printf("Readed\n");
    average = mean(data1, size);
    printf("Average\n");

    printf("Average: %8.3f abcd\n", average);*/

    return 0;

}

/*int main() {
    FILE * finput;

    int i, b[3];
    char *a[3][10];
    char *c[3][10];

    finput = fopen("data.txt", "r");

    for (i = 0; i < 3; i++) {
        fscanf(finput, "%s %d %s\n", a[i], &(b[i]), c[i]);
        printf("%s %d %s\n", *(a[i]), b[i], *(c[i]));
    }

    fclose(finput);
    return 0;
}*/