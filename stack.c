#include "stdlib.h"
#include "string.h"
#include <stdio.h>
#include "stack.h"
stack_t *stack_new(size_t capacity) {
  stack_t *t = (stack_t *)malloc(sizeof(stack_t));
  if (t == NULL) {
    exit(EXIT_FAILURE);
  }
  t->count = 0;
  t->capacity = capacity;
  t->data = malloc(t->capacity * sizeof(void *));
  if (t->data == NULL) {

    free(t);
    exit(EXIT_FAILURE);
  }

  return t;
}

void stack_push(stack_t *stack, void *obj) {
  if (stack->count == stack->capacity) {
    size_t cap = stack->capacity * 2;

    void **data = realloc(stack->data, stack->capacity * sizeof(void *));
    if (NULL == data) {
      sprintf(stderr, "fatal: unable to realloc memory.\n");
      free(stack);
      exit(EXIT_FAILURE);
    }
    stack->capacity = cap;
    stack->data = data;
  }

  stack->data[stack->count] = obj;
  stack->count++;
  return;
}

void *stack_pop(stack_t *stack) {
  if (stack == NULL || stack->count == 0) {
    return NULL;
  }

  void *popped_value = stack->data[stack->count];
  stack->count--;
  return popped_value;
}
void stack_free(stack_t *stack) {

  if (stack == NULL || stack->data == NULL) {
    return;
  }

  free(stack->data);
  free(stack);
  return;
}
void stack_remove_nulls(stack_t *stack){

    int index=0;
    for (int i= 0;i<stack->count;i++){
        if (stack->data[i] != NULL){
            stack->data[index] = stack->data[i];
        }
    }
    for (int i= index;i<stack->capacity;++i){
            stack->data[index] =NULL;
    }
        stack->count=index;
}
