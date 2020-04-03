#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define define_vector(name,type)     \
typedef struct vector_##name{   \
    type*A;                    \
    int n;                      \
    int cap;                    \
    }vector_##name;                    \

#define init_vector(var,type)                               \
    do{                                                     \
        var->cap = 15;                                      \
        var->n = 0;                                         \
        var->A = (type *)malloc(sizeof(type)*var->cap);     \
    }while(0)


#define vector_add(var,type,value)                                    \
    do{                                                               \
        if (var->cap == var->n) {                                     \
        var->cap = (int)(1.5 * (float)var->cap);                      \
        type* B = (type*)malloc(sizeof(type)*var->cap);               \
        memcpy(B,var->A,var->n*sizeof(type));                         \
        free(var->A);                                                 \
        var->A = B;                                                   \
        }                                                             \
        var->A[var->n++] = value;                                     \
    }while(0)

#define vector_free(var)        \
        do{                     \
            free(var->A);       \
            var->A = NULL;      \
        }while(0)               \

define_vector(char_arr,char*)

static char** generateParenthesis(int n, int* returnSize)
{
    int left=0, right=0,count = 0;
    char *stack = malloc(2 * n + 1);
    char *p = stack;
    vector_char_arr * res = (vector_char_arr*)malloc(sizeof(vector_char_arr));
    init_vector(res,char*);
    stack[2 * n] = '\0';
    while (p != stack || count == 0) {
        if (left == n && right == n) {
            char* getOne = (char*)malloc(2 * n + 1);
            strcpy(getOne, stack);
            vector_add(res,char*,getOne);
            count++;
            while (--p != stack) {
                if (*p == '(') {
                    if (--left > right) {
                        *p++ = ')';
                        right++;
                        break;
                    }
                } else {
                    right--;
                }
            }
        } else {
            while (left < n) {
                *p++ = '(';
                left++;
            }
            while (right < n) {
                *p++ = ')';
                right++;
            }
        }
    }
//    *returnSize = res->cap;
    *returnSize = res->n;
    free(stack);
    return res->A;
}


int main() {//memory leak?
        int size;
        char **res;
    res = generateParenthesis(3,&size);
    for(int i=0;i<size;i++){
        printf("%s",res[i]);
        if(res[i]){
            free(res[i]);
        }
    }
    printf("\n");
    free(res);
}
