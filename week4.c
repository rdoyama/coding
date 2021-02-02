/* Week 4 - Reading integers from file */

#include<stdio.h>
#include<stdlib.h>

int* read_file(FILE *ptr)
{
    int i = 0, size;
    int *array;

    size = *ptr;
    array = (int*) malloc(size * sizeof(int));
    for (i; i < size; i++)
        array[i] = *(ptr + i + 1);
    return array;
}

void print_array(int *array)
{
    int i = 0;

    while (*array != '\0')
    {
        printf("%d\t", *(array + i));
        i++;
    }
}

int main(void)
{
    FILE *ptr;
    int *array;

    ptr = fopen("data.txt", "r");
    array = read_file(ptr);
    print_array(array);

    return 0;
}