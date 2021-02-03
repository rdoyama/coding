/* Week 4 - Reading integers from file

   For this assignment, we suppose that each row
   of the file contains only one integer
   We also assume that there are no errors in
   the input file and the size of the array is > 0. */

#include<stdio.h>
#include<stdlib.h>

// Reads the file that starts at ptr and assign
// the values to "array"
void read_file(FILE *ptr, int **array, int size)
{
    int i = 0, x;
    for (i; i < size; i++)
    {
        fscanf(ptr, "%d", (*array + i));
    }
}

// Prints an array of given size
void print_array(int array[], int size)
{
    int i = 0;

    for (i; i < size; i++)
        printf("%d\t", array[i]);
    printf("\n\n");
}

// Computes the average of a array. Size > 0
double mean(int array[], int size)
{
    double average = 0.0;
    int i = 0;

    for (i; i < size; i++)
        average += array[i];
    
    return average / size;
}

// Finds the array's maximum. Size > 0
int max(int array[], int size)
{
    int i = 1, mx = array[0];
    for (i; i < size; i++)
    {
        if (array[i] > mx)
            mx = array[i];
    }
    return mx;
}

int main(void)
{
    FILE *input_file, *output_file;
    int *array, size, maximum;
    double average;

    // File pointer and array size
    input_file = fopen("data.txt", "r");
    fscanf(input_file, "%d", &size);
    printf("Array size: %d\n", size);

    // Memory allocation, reading and printing the original array
    array = (int*) malloc(size * sizeof(int));
    read_file(input_file, &array, size);
    printf("Original array:\n");
    print_array(array, size);

    // Computes average and maximum
    average = mean(array, size);
    printf("Average = %f\n", average);
    maximum = max(array, size);
    printf("Max = %d\n", maximum);

    // Prints the average and maximum to the output file
    // The first line contains the average and the second
    // stores the maximum
    output_file = fopen("answer-hw3", "w");
    fprintf(output_file, "%.3f\n", average);
    fprintf(output_file, "%d\n", maximum);

    // Close files
    fclose(input_file);
    fclose(output_file);

    return 0;
}