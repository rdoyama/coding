/* Week 3 Assignment - Honors
Doubly Linked List with elements ranging
from 0 to 49 will be sorted with MergeSort
to remove duplicates */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// Doubly linked list structure
typedef struct DoublyLinkedListNode
{
    int data;
    struct DoublyLinkedListNode *left, *right;
} DLLNode;

// Creates a single node with data = d
DLLNode* initialize(int d)
{
    DLLNode *new_node = (DLLNode*) malloc(sizeof(DLLNode));
    new_node -> data = d;
    new_node -> left = NULL;
    new_node -> right = NULL;

    return new_node; 
}

// Adds a new node at the end with value d
// Returns the added node
DLLNode* append(DLLNode *node, int d)
{
    DLLNode *tail = initialize(d);
    if (node == NULL)
        return tail;
    while (node -> right != NULL)
        node = node -> right;
    node -> right = tail;
    tail -> left = node;
    return tail;
}

// Prints all nodes after the given node in the
// format [x1, x2, ..., xn]
void print_nodes(DLLNode *node)
{
    if (node != NULL)
    {
        printf("[%d", node -> data);
        node = node -> right;
    }
    while (node != NULL)
    {
        printf(", %d", node -> data);
        node = node -> right;
    }
    printf("]\n\n");
}

// Generates a random doubly linked list
// of size S > 0 with elements in [0, N[.
// Returns the head of the new dllist
DLLNode* random_dllist(int S, int N)
{
    DLLNode *new_node, *head;
    int i = 0;

    srand(time(0));

    head = new_node = initialize(rand() % N);
    for (i; i < S - 1; i++)
    {
        new_node = append(new_node, rand() % N);
    }
    return head;
}

// Returns the size of the doubly linked list
int get_size(DLLNode *head)
{
    int i = 0;
    while (head != NULL)
    {
        head = head -> right;
        i++;
    }
    return i;
}

// Merges 2 sorted doubly linked lists
DLLNode* merge(DLLNode *head1, DLLNode *head2)
{
    DLLNode *next_node, *temp;

    if (head1 == NULL)
        return head2;
    else if (head2 == NULL)
        return head1;
    
    if (head1 -> data <= head2 -> data)
    {
        next_node = head1;
        temp = merge(head1 -> right, head2);
        temp -> left = next_node;
        next_node -> right = temp;
    }
    else
    {
        next_node = head2;
        temp = merge(head1, head2 -> right);
        temp -> left = next_node;
        next_node -> right = temp;
    }
    return next_node;    
}

// Deletes the node in the right
void delete_right(DLLNode *node)
{
    DLLNode *temp;
    
    // Node is the tail
    if (node -> right == NULL || node == NULL)
        return;
    // Node before tail
    else if (node -> right -> right == NULL)
    {
        temp = node -> right;
        node -> right = NULL;
    }
    else
    {
        temp = node -> right;
        node -> right = temp -> right;
        temp -> right -> left = node;
    }
    free(temp);
}

// Removes duplicates from the sorted DLList
void rm_duplicates(DLLNode *head)
{
    DLLNode *current = head, *temp;
    int quit = 0;

    while (current -> right != NULL)
    {
        while (current -> right -> data == current -> data)
        {
            delete_right(current);
            if (current -> right == NULL)
            {
                quit = 1;
                break;
            }
        }
        if (quit)
            break;
        current = current -> right;
    }
}

// MergeSort algorithm
DLLNode* merge_sort(DLLNode *node)
{
    int size = get_size(node);
    int middle = (size - 1) / 2, i = 0;
    DLLNode *current = node, *node2, *head1, *head2;

    // Base case
    if (node == NULL || size == 1)
        return node;
    
    while (i++ != middle)
        current = current -> right;
    
    // Separates the list
    node2 = current -> right;
    current -> right = NULL;
    node2 -> left = NULL;

    head1 = merge_sort(node);
    head2 = merge_sort(node2);
    return merge(head1, head2);
}

int main(void)
{
    DLLNode *head;
    // Choose size and range
    int size = 200, range = 50;

    // Generate list
    head = random_dllist(size, range);
    printf("Original List:\n");
    print_nodes(head);

    // Sorted List
    head = merge_sort(head);
    printf("Sorted List:\n");
    print_nodes(head);

    // List without duplicates
    rm_duplicates(head);
    printf("Without Duplicates:\n");
    print_nodes(head);

    return 0;
}