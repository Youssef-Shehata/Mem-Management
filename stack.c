#include "stdlib.h"
#include "string.h"
#include <stdio.h>

#include "stack.h"
stack_t *stack_new(size_t capacity) {
  stack_t *t = (stack_t *)malloc(capacity * sizeof(stack_t));
  if (t == NULL) {
    return NULL;
  }
  t->data = (void **)malloc(capacity * sizeof(void *));
  if (t->data == NULL) {

    free(t);
    return NULL;
  }

  t->count = 0;
  t->capacity = capacity;
  return t;
}

void stack_push(stack_t *stack, void *obj) {
  if (stack->count == stack->capacity) {
    size_t cap = stack->capacity * 2;

    void **data =
        (void *)realloc(stack->data, stack->capacity * sizeof(void *));
    if (data == NULL) {
      free(stack);
      return;
    }
    stack->capacity = cap;
    stack->data = data;
  }

  stack->data[stack->count] = obj;
  stack->count += 1;
  return;
}

void *stack_pop(stack_t *stack) {
  if (stack== NULL) {
    return NULL;
  }

  if (stack->count == 0) {
    return NULL;
  }
  void* popped_value = stack->data[stack->count];
  stack->count--;
  return  popped_value;
}
void stack_free(stack_t *stack) {

  if (stack == NULL) {
    return;
  }

  if (stack->data != NULL) {
    free(stack->data);
  }
  free(stack);
  return;
}




























