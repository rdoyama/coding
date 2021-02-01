/* Week 3 Programming Exercise
Use the linear linked list code to store a 
randomly generated set of 100 integers.

Algorithm: Bubble Sort

Results will be printed in lines of 5
elements. */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// Node: holds information and a second attribute that
// is a pointer to the next item on the list
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// Print data from Node n. Each line contains
// up to N elements
void print_list(Node *n)
{
    int i = 0, N = 5;
    printf("[ ");
    while (1)
    {
        if (n == NULL)
        {   
            printf("]\n");
            break;
        }
        else if (i != 0 && n != NULL)
            printf("\n  ");
        
        i = 0;
        while (n != NULL && i != N)
        {
            printf("%d\t", n -> data);
            n = n -> next;
            i++;
        }
    }
}

// Create a single element from a linked list
// with next = NULL
Node* create_list(int d)
{
    Node *head = (Node*) malloc(sizeof(Node));
    head -> data = d;
    head -> next = NULL;
    return head;
}

// Inserts an element in the end of the list
// Returns the added element
Node* add2end(int d, Node *node)
{
    Node *last = create_list(d);
    while (node -> next != NULL)
    {
        node = node -> next;
    }
    node -> next = last;
}

// Counts the number of elements in the list
int get_size(Node *head)
{
    int i = 0;
    while (head != NULL)
    {
        head = head -> next;
        i++;
    }
    return i;
}

// Swaps two nodes.
void swap(Node *node1, Node *node2)
{
    int temp;

    if (node1 == NULL || node2 == NULL)
        return;
    
    temp = node1 -> data;
    node1 -> data = node2 -> data;
    node2 -> data = temp;
}

// Creates a linked list of size s (s >= 1) with
// integers from 0 to N
Node* random_llist(int s, int N)
{
    Node *head, *tail;
    int i = 1;

    srand(time(0));

    head = create_list((rand() % N));
    tail = head;
    while (i++ < s)
        tail = add2end((rand() % N), tail);
    return head;
}

// Sorts a linked list using optimized BubbleSort
void* bubble_sort(Node *head)
{
    Node *node1, *node2;
    int size = get_size(head);
    int i, j, swp;

    for (i = 0; i < size - 1; i++)
    {
        node1 = head;
        swp = 0;
        for (j = 0; j < size - i - 1; j++)
        {
            node2 = node1 -> next;
            if (node1 -> data > node2 -> data)
            {
                swap(node1, node2);
                swp = 1;
            }
            node1 = node1 -> next;
        }
        if (!swp)
            break;
    }
}

int main(void)
{
    Node *head;

    // Random LList of 100 integer elements ranging
    // from 0 to 99 
    head = random_llist(100, 100);

    // Sorting
    bubble_sort(head);

    // Print the results
    print_list(head);
}