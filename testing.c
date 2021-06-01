///////////////////////////////////////
// tree implementation
///////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
	int data;
	struct tree* left;
	struct tree* right;
} tree;

// inorder printing
void print_tree(tree* root)
{
	if (!root) return;
	if (root->left) print_tree(root->left);
	printf("%d ", root->data);
	if (root->right) print_tree(root->right);
	return;
}

// dealing with tree nodes as pointers
tree* create_node_ptr(int data)
{
	tree* node = malloc(sizeof(tree));
	node->data = data;
	node->left = 0;
	node->right = 0;
	return node;
}

// recursive tree cration from an array
tree* create_from_array(int arr[], const unsigned int size, unsigned int index)
{
	if (index - 1 >= size) return 0;
	tree* node = create_node_ptr(arr[index-1]);
	tree* left_node = create_from_array(arr, size, index*2);
	tree* right_node = create_from_array(arr, size, index*2 + 1);
	node->left = left_node;
	node->right = right_node;
	return node;
}

// cleaning up memory after tree is no longer needed
void del_tree(tree* root)
{
	if (!root) return;
	if (!root->left) del_tree(root->left);
	if (!root->right) del_tree(root->right);
	free(root);
	root = 0;
}


int main (int argc, char* argv[])
{
	if (argc < 2) {
		printf("Please provide input filename!\n");
		return 1;
	}
	FILE* pfile = fopen(argv[1], "r");
	int size = 0;
	fscanf(pfile, "%d", &size);
	int* arr = malloc(sizeof(int)*size);
	printf("Read array:\n");
	// reading data and printing at the same time
	for (unsigned int i = 0; i < size && fscanf(pfile, "%d", &arr[i]) != EOF; i++)
		printf("%d ", arr[i]);
	tree* root = create_from_array(arr, size, 1);
	printf("\nTree printed as inorder:\n");
	print_tree(root);

	// memory clean-up
	del_tree(root);
	free(arr);
	fclose(pfile);
	return 0;
}
