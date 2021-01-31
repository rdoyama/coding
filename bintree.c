/* Binary Tree Structure */

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
        printf("%d\n", node -> data);
        print_elements(node -> right);
    }
}

// Searches the node with data = key
// If the key is found, returns the node containing it,
// else returns the closest node.
BTNode* search(BTNode *node, int key)
{
    if (node -> data > key && node -> left != NULL)
        return search(node -> left, key);
    else if (node -> data < key && node -> right != NULL)
        return search(node -> right, key);
    return node;
}

// Gets the node containing the smallest data value
BTNode* get_smallest(BTNode *node)
{
    if (node -> left == NULL)
        return node;
    return get_smallest(node -> left);
}

// Gets the node containing the biggest data value
BTNode* get_biggest(BTNode *node)
{
    if (node -> right == NULL)
        return node;
    return get_biggest(node -> right);
}

// Deletes a node of data = key
BTNode* delete(BTNode *root, int key)
{
    if (root == NULL)
        return root;
    else if (key < root -> data)
        root -> left = delete(root -> left, key);
    else if (key > root -> data)
        root -> right = delete(root -> right, key);
    else
    {
        if (root -> left == NULL)
        {
            BTNode *temp = root -> right;
            free(root);
            return temp;
        }
        else if (root -> right == NULL)
        {
            BTNode *temp = root -> left;
            free(root);
            return temp;
        }
        BTNode *temp = get_biggest(root -> left);
        root -> data = temp -> data;
        root -> left = delete(root -> left, key);
    }
    return root;
}

int main(void)
{
    BTNode* node = newNode(5);

    insert(node, 5);
    insert(node, 6);
    insert(node, 4);
    insert(node, 3);
    insert(node, 8);
    insert(node, 7);

    print_elements(node);
    printf("\n");

    printf("%d\n", search(node, 5) -> data);
    printf("%d\n", search(node, 10) -> data);
    printf("\n");

    printf("%d\n", get_biggest(node) -> data);
    printf("%d\n", get_smallest(node) -> data);
    printf("\n");

    node = delete(node, 6);
    print_elements(node);
    printf("\n");

    return 0;
}