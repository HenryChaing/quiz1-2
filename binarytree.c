#include <stdio.h>
#include <stdlib.h>

#define container_of(ptr, type, member) \
    ((type *) ((char *) (ptr) - (size_t) & (((type *) 0)->member)))

#define list_entry(ptr, type, member) container_of(ptr, type, member)

#define hlist_for_each(pos, head) \
    for (pos = (head)->first; pos; pos = pos->next)

/*global variable*/
struct TreeNode *node[100];
int front=0, end=0;
int preorder[] = {3,9,20,15,7};
int inorder[] = {9,3,15,20,7};
struct hlist_head *in_heads;
int node_count;

struct hlist_node {
    struct hlist_node *next, **pprev;
};
struct hlist_head {
    struct hlist_node *first;
};

static inline void INIT_HLIST_HEAD(struct hlist_head *h)
{
    h->first = NULL;
}

static inline void hlist_add_head(struct hlist_node *n, struct hlist_head *h)
{
    if (h->first)
        h->first->pprev = &n->next;
    n->next = h->first;
    n->pprev = &h->first;
    h->first = n;
}

struct TreeNode {
    int val;
    struct TreeNode *left, *right;
};

struct order_node {
    struct hlist_node node;
    int val;
    int idx;
};

static int find(int num, int size, const struct hlist_head *heads)
{
    struct hlist_node *p;
    int hash = (num < 0 ? -num : num) % size;
    hlist_for_each (p, &heads[hash]) {
        struct order_node *on = container_of(p, struct order_node, node);
        if (num == on->val)
            return on->idx;
    }
    return -1;
}

static struct TreeNode *dfs(int pre_low,
                            int pre_high,
                            int in_low,
                            int in_high)
{
    if (in_low > in_high || pre_low > pre_high)
        return NULL;

    struct TreeNode *tn = malloc(sizeof(*tn));
    tn->val = preorder[pre_low];
    int idx = find(preorder[pre_low], node_count, in_heads);
    tn->left = dfs(pre_low + 1, pre_low + (idx - in_low),
                   in_low, idx - 1);
    tn->right = dfs(pre_high - (in_high - idx - 1), pre_high,
                    idx + 1, in_high);
    return tn;
}

static inline void node_add(int val,
                            int idx,
                            int size,
                            struct hlist_head *heads)
{
    struct order_node *on = malloc(sizeof(*on));
    on->val = val;
    on->idx = idx;
    int hash = (val < 0 ? -val : val) % size;
    hlist_add_head(&on->node, &heads[hash]);
}

static struct TreeNode *buildTree()
{
    in_heads = malloc(node_count * sizeof(*in_heads));
    for (int i = 0; i < node_count; i++)
        INIT_HLIST_HEAD(&in_heads[i]);
    for (int i = 0; i < node_count; i++)
        node_add(inorder[i], i, node_count, in_heads);

    return dfs( 0, node_count - 1,  0, node_count - 1);
}

void level_order_search(struct TreeNode *BT){
    node[end++] = BT;
    printf("BFS ( binarytree ) = [ ");
    while(front != end){
        struct TreeNode *pop_node = node[front++];
        if(!pop_node){
            printf("NULL, ");
        }else{
            printf("%d, ",pop_node->val);
            node[end++] = pop_node->left;
            node[end++] = pop_node->right;
        }
    }
    printf(" ]\n");
}

int main(){
    node_count = sizeof(inorder)/sizeof(inorder[0]);
    struct TreeNode *BT = buildTree();
    level_order_search(BT);
}