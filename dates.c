/* Using enumerators to define
the days of the year (except Leap Years) 
Make sure the input date is valid 

If you have good knowledge of C Language, 
please leave comments about my code, regarding
efficiency, data structures, good practices, etc.
Thank You! */

#include<stdio.h>

// Enumerating months
typedef enum month {jan, feb, mar, apr, may, jun,
        jul, aug, sep, oct, nov, dec} month;

// Define date structure
typedef struct date
{
    month m;
    int d;
} date;

// Assign a month and a day to variable of type date
void assign_date(date *dt, month mo, int day)
{
    dt -> d = day;
    dt -> m = mo;
}

// Calculates the next day
date next_day(date *dt)
{
    date tomorrow;
    int M = dt -> m, D = dt -> d, newM, newD;
    int daysInMonth[12] = {31, 28, 31, 30, 31, 
            30, 31, 31, 30, 31, 30, 31};

    // Month increase
    if ((D + 1) % daysInMonth[M] == 1)
        newM = (M + 1) % 12;
    else
        newM = M;
    
    // Day increase
    newD = (D + 1) % daysInMonth[M];

    assign_date(&tomorrow, newM, newD);

    return tomorrow;
}

void print_day(date *dt)
{
    int M = dt -> m, D = dt -> d;
    switch(M)
    {
        case 0: printf("January "); break;
        case 1: printf("February "); break;
        case 2: printf("March "); break;
        case 3: printf("April "); break;
        case 4: printf("May "); break;
        case 5: printf("June "); break;
        case 6: printf("July "); break;
        case 7: printf("August "); break;
        case 8: printf("September "); break;
        case 9: printf("October "); break;
        case 10: printf("November "); break;
        case 11: printf("December "); break;
    }
    printf("%d\n", D);  
}

int main(void)
{
    // 4 dates given in the exercise
    date dates[4] = {{1, 28}, {mar, 14}, {oct, 31}, {dec, 31}};
    date tomorrow;

    int i;

    for (i=0; i < 4; i++)
    {
        print_day(&dates[i]);
        tomorrow = next_day(&dates[i]);
        print_day(&tomorrow);
        printf("\n");
    }

    return 0;
}