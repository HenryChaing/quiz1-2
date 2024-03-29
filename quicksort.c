#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

void determine_med(node_t *L,node_t *M,node_t *R)
{
    long L_value = L->value;
    long M_value = M->value;
    long R_value = R->value;
    
    if(L_value > R_value){
        if(L_value > M_value){
            if(R_value > M_value){
                R->value = L_value;
                L->value = R_value;
            }else{
                M->value = L_value;
                L->value = M_value;
            }
        }
    }else{
        if(R_value > M_value){
            if(L_value <= M_value){
                M->value = L_value;
                L->value = M_value;
            }
        }else{
            R->value = L_value;
            L->value = R_value;
        }
    }
}

/* Verify if list is order */
static bool list_is_ordered(node_t *list)
{       
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

/* shuffle array, only work if n < RAND_MAX */
void shuffle(int *array, size_t n)
{
    if (n <= 0)
        return;

    for (size_t i = 0; i < n - 1; i++) {
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

void quick_sort(node_t **list)
{
    int n = list_length(list);
    int value;
    int i = 0;
    int max_level = 2 * n;
    node_t *begin[max_level], *end[max_level];
    node_t *result = NULL, *left = NULL, *right = NULL;
    
    begin[0] = *list;
    end[0] = list_tail(list);
            
    while (i >= 0) {
        node_t *L = begin[i], *R = end[i];
        if (L != R) {
            /*adapt midian of three*/
            /*middle is lowbound of n/2*/
            node_t *M = list_mid(&L);
            /*find the median*/
            determine_med(L,M,R);
            
            /*
            node_t *M = list_random(&L);
            long temp = M->value;
            M->value = L->value;
            L->value = temp;
            */
            node_t *pivot = L;
            value = pivot->value;
            node_t *p = pivot->next;
            pivot->next = NULL;
    
            while (p) {
                node_t *n = p;
                p = p->next;
                list_add(n->value > value ? &right : &left, n);
            }

            begin[i] = left;
            end[i] = list_tail(&left);
            begin[i + 1] = pivot;
            end[i + 1] = pivot;
            begin[i + 2] = right;
            end[i + 2] = list_tail(&right);

            left = right = NULL;
            i += 2;
        } else {
            if (L)
                list_add(&result, L);
            i--;
        }
    }
    *list = result;
}

int main(int argc, char **argv)
{
    node_t *list = NULL;
    clock_t t;
    size_t count = 100000;

    int *test_arr = malloc(sizeof(int) * count);

    for (int i = 0; i < count; ++i)
        test_arr[i] = i;
    shuffle(test_arr, count);

    while (count--)
        list = list_construct(list, test_arr[count]);
    
    t = clock();
    quick_sort(&list);
    t = clock() - t;
    printf("%f seconds.\n",((float)t) / CLOCKS_PER_SEC);

    assert(list_is_ordered(list));
    

    list_free(&list);

    free(test_arr);

}

