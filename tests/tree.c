#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node
{
    int val;
    struct tree_node *left;
    struct tree_node *right;
}
tree_node;

void insert_left_child(tree_node *root, int val);
void insert_right_child(tree_node *root, int val);
void insert_children_furthest(tree_node *root, int valleft, int valright, char direction);
void free_tree(tree_node *root);
void print_tree_binary_search(tree_node *root);

int main(void)
{
    tree_node *root = malloc(sizeof(tree_node));
    root->val = 6;
    root->left = NULL;
    root->right = NULL;
    insert_children_furthest(root, 4, 8, 'N');
    insert_children_furthest(root, 3, 5, 'L');
    insert_children_furthest(root, 7, 9, 'R');
    //printf("Left node address: %p, Right node address: %p\n", root->left, root->right);
    //printf("Left node val: %i, Right node val: %i\n", (root->left)->val, (root->right)->val);
    print_tree_binary_search(root);
    free_tree(root);
}

void insert_children_furthest(tree_node *root, int valleft, int valright, char direction)
{
    tree_node *nodeleft = malloc(sizeof(tree_node));
    tree_node *noderight = malloc(sizeof(tree_node));

    if (direction == 'L')
    {
        while (root->left != NULL)
        {
            root = root->left;
        }
    }

    else if (direction == 'R')
    {
        while (root->right != NULL)
        {
            root = root->right;
        }
    }

    root->left = nodeleft;
    root->right = noderight;
    nodeleft->val = valleft;
    noderight->val = valright;
    nodeleft->left = NULL;
    nodeleft->right = NULL;
    noderight->left = NULL;
    noderight->right = NULL;
}



void free_tree(tree_node *root) //Implement complete tree traversal, probably best to do so with recursion?
{
    if (root == NULL) // When recieving an input of a pointer to a node that doesnt exist, AKA NULL, it means that we have reached the end of the tree.
    {
        return;
    }

    /*
    Will traverse all the way to the leftmost child, once it reaches that point it passes a non-existing node, aka NULL and thus the if condition will proc and return with nothing having happend,
    then itll attempt the next line argument, trying to free a right child of the left most node, after finishing checking and either diving deeper or just returning again with nothing happend
    the node will be released as it points to nothing, and then the function call will move one layer up, to the new leftmost child, and itll check if it has right children, if it does, itll
    traverse it till the end and free the nodes one by one until it returns to the parent node, this proccess will be repeated until nothing remains */
    free_tree(root->left); // Recursively goes to the left child, if it doesnt exist will return with nothing having happend.
    free_tree(root->right); // Recursively goes to the right child, if it doesnt exist will return with nothing having happend.
    free(root); // Frees the node, will happen once it reaches the last node that doesnt point to anything, and after freeing each node one by one and going up the function call eventually all nodes will be freed.
}

void print_tree_binary_search(tree_node *root)
{
    if (root == NULL)
    {
        return;
    }
    print_tree_binary_search(root->left);
    printf("Node: %i\n", root->val);
    print_tree_binary_search(root->right);
    return;
}







void insert_left_child(tree_node *root, int val) // Should technically return an int and check whether node returns a valid pointer and not NULL but meh.
{
    tree_node *node = malloc(sizeof(tree_node));
    while (root->left != NULL)
    {
        root = root->left;
    }
    root->left = node;
    node->val = val;
    node->left = NULL;
    node->right = NULL;
}

void insert_right_child(tree_node *root, int val) // Should technically return an int and check whether node returns a valid pointer and not NULL but meh.
{
    tree_node *node = malloc(sizeof(tree_node));
    while (root->right != NULL)
    {
        root = root->right;
    }
    root->right = node;
    node->val = val;
    node->right = NULL;
    node->left = NULL;
}
