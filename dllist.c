/* DouDoublyble Linked List */

#include<stdio.h>
#include<stdlib.h>

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

// Adds a new node at the end
void append(DLLNode *node, int d)
{
    DLLNode *new_node = initialize(d);
    if (node == NULL)
        return;
    while (node -> right != NULL)
        node = node -> right;
    node -> right = new_node;
    new_node -> left = node;
}

// Adds a new node at the start
DLLNode* addFirst(DLLNode *node, int d)
{
    DLLNode *new_node = initialize(d);
    if (node == NULL)
        return new_node;
    while (node -> left != NULL)
        node = node -> left;
    node -> left = new_node;
    new_node -> right = node;
    return new_node;
}

// Prints all nodes after the given node
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
    printf("]\n");
}

// Print backwards - Use to check if merge was a success
void print_back(DLLNode *node)
{
    while (node -> right != NULL)
        node = node -> right;
    while (node != NULL)
    {
        printf("%d\t", node -> data);
        node = node -> left;
    }
}

// Inserts an element at the index n
DLLNode* insert(DLLNode *head, int index, int d)
{
    int i = 0;
    DLLNode *current = head, *temp;

    if (index == 0)
        return addFirst(head, d);
    while (i + 1 != index)
    {
        current = current -> right;
        if (current == NULL)
        {
            printf("Index %d out of range (%d)\n", index, i);
            return head;
        }
        i++;
    }
    temp = initialize(d);
    temp -> right = current -> right;
    temp -> left = current;
    current -> right -> left = temp;
    current -> right = temp;
    return head;
}

// Inserts a new node after the given node
// Note that
DLLNode* insert_after(DLLNode *node1, DLLNode *node2)
{
    if (node2 == NULL)
        return node1;
    if (node1 == NULL)
        return node2;
    if (node1 -> right == NULL)
    {
        node1 -> right = node2;
        node2 -> left = node1;
        return node2;
    }
}

// Inserts node2 at the end of node1
DLLNode* append_node(DLLNode *node1, DLLNode *node2)
{
    DLLNode *head = node1;
    if (node2 == NULL)
        return node1;
    if (node1 == NULL)
        return node2;
    while (node1 -> right != NULL)
        node1 = node1 -> right;
    node1 -> right = node2;
    node2 -> left = node1;
    node2 -> right = NULL;
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

DLLNode* merge_sort(DLLNode *node)
{
    int size = get_size(node);
    int middle = (size - 1) / 2, i = 0;
    DLLNode *current = node, *node2, *head1, *head2;

    if (node == NULL || size == 1)
        return node;
    while (i != middle)
    {
        current = current -> right;
        i++;
    }
    node2 = current -> right;
    current -> right = NULL;
    node2 -> left = NULL;

    head1 = merge_sort(node);
    head2 = merge_sort(node2);
    return merge(head1, head2);
}

int main(void)
{
    DLLNode *head = initialize(6), *head2 = initialize(8);
    DLLNode *merged;

    append(head, 7);
    append(head, 8);
    append(head, 12);
    append(head, 8);
    head = addFirst(head, 5);
    head = addFirst(head, 4);
    head = addFirst(head, 3);
    head = addFirst(head, 2);
    head = addFirst(head, 1);
    //head = insert(head, 8, 15);

    append(head2, 6);
    append(head2, 4);
    append(head2, 2);

    print_nodes(head);
    printf("Size: %d\n", get_size(head));

    //merged = merge(head, head2);
    //print_nodes(merged);
    //print_back(merged);

    merged = merge_sort(head);
    print_nodes(merged);
    print_back(merged);

    return 0;
}