/* Linked lists */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

// Node: holds information and a second attribute that
// is a pointer to the next item on the list
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// Print data from Node n
void print_list(Node *n)
{
    printf("[%d", n -> data);
    n = n -> next;
    while (n != NULL)
    {
        printf(", %d", n -> data);
        n = n -> next;
    }
    printf("]\n");
}

// Checks if the Node n is empty
int is_empty(const Node *n)
{
    return (n == NULL);
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

// Inserts an element in the first position
Node* add2front(int d, Node *head)
{
    Node *first = create_list(d);

    first -> next = head;

    return first;
}

// Inserts an element in the end of the list
void add2end(int d, Node *head)
{
    Node *last = create_list(d);
    while (head -> next != NULL)
    {
        head = head -> next;
    }
    head -> next = last;
}

// Removes the first element from the list
Node* remove_first(Node *head)
{
    Node *next = head -> next;
    free(head);
    return next;
}

// Removes the element of index n from the list
Node* remove_n(Node *head, int n)
{
    Node *current = head, *temp;
    int i = 0;
    if (n == 0)
        return remove_first(head);
    while (i++ != n - 1)
    {
        if (current -> next == NULL)
        {
            printf("List Index (%d) out of range (%d)\n", n, i - 1);
            return head;
        }
        current = current -> next;
    }
    temp = current -> next;
    current -> next = current -> next -> next;
    free(temp);
    return head;
}

// Inserts an element in the index n
Node* insert_n(int d, int n, Node *head)
{
    Node *new = create_list(d);
    Node *current = head, *temp;
    int i = 0;

    if (n == 0)
        return add2front(d, head);

    while (i++ != n - 1)
    {
        if (current -> next == NULL)
        {
            printf("List Index (%d) out of range (%d)\n", n, i - 1);
            return head;
        }
        current = current -> next;
    }

    temp = current -> next;
    current -> next = new;
    new -> next = temp;

    return head;
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

// Converts an array to a linked list
// Returns the head
Node* array2list(int array[], int array_size)
{
    Node *head = create_list(array[array_size - 1]);
    int i = array_size - 2;

    for (i; i >= 0; i--)
    {
        head = add2front(array[i], head);
    }

    return head;
}

// Merges 2 linked lists. The last element from the first list
// points to the first element in the second list.
Node* concat(Node *head1, Node *head2)
{
    Node *current = head1;
    if (head1 == NULL)
        return head2;
    while (current -> next != NULL)
        current = current -> next;
    current -> next = head2;
    return head1;
}

// Transforms a linked list in a list
// Returns a pointer to the list
int* llist2list(Node* head)
{
    int size = get_size(head);
    // Variable sized array requires malloc
    // If a array filled with zeroes is needed, use
    // memset(arr, 0, size*sizeof(int)) #include<string.h>
    int *list = malloc(size*sizeof(int));
    int i = 0;

    while (head != NULL)
    {
        list[i++] = head -> data;
        head = head -> next;
    }

    return list;
}

// Prints an array
// len(array) must be larger than 1
void print_array(int *list, int size)
{
    int i = 1;
    printf("[%d", *list);
    for (i; i < size; i++)
        printf(", %d", *(list + i));
    printf("]\n");
}

// Swaps two nodes
void swap(Node *node1, Node *node2)
{
    int temp;

    if (node1 == NULL)
        return;
    else if (node2 == NULL)
        return;
    
    temp = node1 -> data;
    node1 -> data = node2 -> data;
    node2 -> data = temp;
}

// Sorts a linked list using BubbleSort
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

// Merges 2 sorted linked lists
Node* merge(Node *head1, Node* head2)
{
    Node *next_node, *temp;

    if (head1 == NULL)
        return head2;
    else if (head2 == NULL)
        return head1;
    
    if (head1 -> data <= head2 -> data)
    {
        next_node = head1;
        temp = merge(head1 -> next, head2);
        next_node -> next = temp;
    }
    else
    {
        next_node = head2;
        temp = merge(head1, head2 -> next);
        next_node -> next = temp;
    }
    return next_node; 
}

// MergeSort Algorithm
Node* merge_sort(Node* node)
{
    int size = get_size(node);
    int middle = (size - 1) / 2, i = 0;
    Node *current = node, *node2, *head1, *head2;

    if (node == NULL || size == 1)
        return node;
    while (i != middle)
    {
        current = current -> next;
        i++;
    }
    node2 = current -> next;
    current -> next = NULL;

    head1 = merge_sort(node);
    head2 = merge_sort(node2);
    return merge(head1, head2);
}

int main(void)
{
    Node *head = NULL, *head2 = NULL, *head3 = NULL;
    int data1[5] = {1, 2, 3, 4, 5};
    int data2[6] = {4, 2, 5, 3, 6, 7};
    int size, i = 0;
    int *list;

    head = array2list(data1, 5);
    head2 = array2list(data2, 6);

    add2end(7, head);
    head = remove_first(head);
    head = remove_n(head, 7);
    head = insert_n(8, 0, head);
    size = get_size(head2);
    printf("Size = %d\n", size);
    print_list(head);
    head = concat(head2, head);

    print_list(head);

    list = llist2list(head);
    swap(head, head -> next);
    merge_sort(head);
    print_list(head);

    print_array(list, get_size(head));

    return 0;
}