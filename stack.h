#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
typedef struct Stack {
  size_t count;
  size_t capacity;
  void **data;
} stack_t;

stack_t *stack_new(size_t capacity);
void *stack_pop(stack_t *stack);
void stack_push(stack_t *stack, void *obj);

void stack_free(stack_t *stack);
void stack_remove_nulls(stack_t *stack);

