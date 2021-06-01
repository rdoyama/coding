/* Week 4 Assignment with Honors

   Transforming an array into a binary tree
   and printing its elements.
   
   The array is readed from a file given in the
   command line. The first element of the file is
   the number of integers ahead. We assume that
   the file structure is correct and it looks like
   this:
   
   "
   3
   6
   5
   8
   "
   
   */

#include<stdio.h>
#include<stdlib.h>

// BinTree Structure
typedef struct BinTreeNode
{
    int data;
    struct BinTreeNode *left, *right;
} BTNode;

// Returns a new node with data = d 
BTNode* newNode(int d)
{
    BTNode *node = (BTNode*) malloc(sizeof(BTNode));

    node -> data = d;
    node -> left = NULL;
    node -> right = NULL;

    return node;
}

// Inserts the integer d in the tree if it is not present
BTNode* insert(BTNode *node, int d)
{
    if (node == NULL)
        return newNode(d);
    if (d < node -> data)
        node -> left = insert(node -> left, d);
    else if (d > node -> data)
        node -> right = insert(node -> right, d);
    return node;
}

// Prints the elements from left to right up to the node
void print_elements(BTNode *node)
{
    if (node != NULL)
    {
        print_elements(node -> left);
        printf("%d\t", node -> data);
        print_elements(node -> right);
    }
}

// Reads the file and adds the integers to the array
void file2array(FILE *ptr, int **array, int size)
{
    int i = 0;
    for (i; i < size; i++)
        fscanf(ptr, "%d", (*array + i));
}

// Transforms a non-empty array into a Binary Tree
// Returns the first element of the array as the root
// of the tree.
BTNode* array2bintree(int array[], int size)
{
    BTNode *root;
    int i = 1;

    root = newNode(array[0]);

    for (i; i < size; i++)
        root = insert(root, array[i]);
    
    return root;
}

int main(int argc, char *argv[])
{
    FILE *input;
    int size, *array;
    BTNode *root;

    if (argc != 2)
    {
        printf("\nTo execute correctly, use -> $ ./week4-honors file.txt\n\n");
        return 1;
    }

    input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("\nError: No such file or directory\n\n");
        return 1;
    }

    // Reads the file into "array"
    fscanf(input, "%d", &size);
    array = (int*) malloc(size * sizeof(int));
    file2array(input, &array, size);

    // Transforms the array into a Binary Tree
    root = array2bintree(array, size);

    printf("\n  Binary Tree 'inorder':\n");
    print_elements(root);
    printf("\n\n");

    fclose(input);

    return 0;
}