#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
    int val;
    struct node *next;
}
node;




int insert_node_end(node *head, int val);
void print_nodes(node *node);
void free_nodes(node *head);

int main(void)
{
    node *head = malloc(sizeof(node)); // Assigns an available address the size of node to the variable head
    if (head == NULL)
    {
        return 1;
    }
    head->val = 3; // Goes to the address inside the variable head, and sets the member val of the address in head to 3.
    head->next = NULL; // Points to nothing

    int x;
    x = insert_node_end(head, 8);
    if (x == 1)
    {
        free_nodes(head);
        return 1;
    }

    x = insert_node_end(head, 12);
    if (x == 1)
    {
        free_nodes(head);
        return 1;
    }

    print_nodes(head);
    free_nodes(head);
}

int insert_node_end(node *head, int val)
{
    node *node = malloc(sizeof(node));
    if (node == NULL)
    {
        return 1;
    }

    while (head->next != NULL) // Traverses the list until the last node. The last nodes next value will be NULL. End of while loop node should be set to the last valid node.
    {
        head = head->next;
    }
    head->next = node; // Point last node to new node
    node->val = val; // Set value of the new node to val
    node->next = NULL; // Point the new(last) node to NULL
    return 0;
}

void print_nodes(node *node)
{
    while (node != NULL)
    {
        printf("Current node value: %i\n", node->val);
        node = node->next;
    }
}

void free_nodes(node *head)
{
    while (head != NULL)
    {
        node *tmp = head;
        head = head->next;
        free(tmp);
    }
}