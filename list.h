#include <stdlib.h>

typedef struct __node {
    struct __node *left, *right;
    struct __node *next;
    long value;
} node_t;

void list_add(node_t **list, node_t *node_t)
{
    node_t->next = *list;
    *list = node_t;
}

node_t *list_tail(node_t **left)
{
    while ((*left) && (*left)->next)
        left = &((*left)->next);
    return *left;
}

int list_length(node_t **left)
{
    int n = 0;
    while (*left) {
        ++n;
        left = &((*left)->next);
    }
    return n;
}

/*lead to mid node*/
node_t *list_mid(node_t **left)
{
    node_t *slow,*fast;
    slow = fast = &left;
    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }    
    return slow;
}

/*lead to random node*/
node_t *list_random(node_t **left)
{
    int random = rand()%list_length(left) -1;
    for (int i = 0; i < random; i++)
    {
        left = &((*left)->next);
    }    
    return *left;
}

node_t *list_construct(node_t *list, int n)
{
    node_t *node = (node_t *) malloc(sizeof(node_t));
    node->next = list;
    node->value = n;
    return node;
}

void list_free(node_t **list)
{
    node_t *node = (*list)->next;
    while (*list) {
        free(*list);
        *list = node;
        if (node)
            node = node->next;
    }
}