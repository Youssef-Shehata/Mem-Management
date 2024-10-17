#include <stdio.h>
#include <stdlib.h>

void allocate_int(int **pointer_pointer, int value);
typedef struct Token {
    char* literal;
    int line;
    int column;
} token_t;

token_t** create_token_pointer_array(token_t* tokens, size_t count);
void swap(void*a, void *b,size_t s) ;

typedef struct Stack {
  size_t count;
  size_t capacity;
  void **data;
} stack_t;

stack_t *stack_new(size_t capacity);
void *stack_pop(stack_t *stack);
void stack_push(stack_t *stack, void *obj);

