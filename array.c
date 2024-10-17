


#include <stdio.h>
#include <string.h>
#include "stdlib.h"

#include "object.h"
array_t*new_array(size_t size){


  array_t*arr= malloc(sizeof(array_t));
  if (NULL == arr) {
    fprintf(stderr, "Failed to allocate heap memory.\n");
    return NULL;
  }

  arr->elements= calloc(size ,sizeof(void *));
  if (NULL == arr->elements) {
    fprintf(stderr, "Failed to allocate heap memory.\n");
    free(arr);
    return NULL;
  }

  arr->size= size ;

  return arr;

}



//void *array_pop(array_t*vec) {
//  if (NULL == vec) {
//
//    fprintf(stderr, "Trying to pop from a NULL pointer.\n");
//    return NULL;
//  }
//
//  if (vec->count == 0) {
//    fprintf(stderr, "Popping from an empty vector.\n");
//    return NULL;
//  }
//
//  void *popped_value = vec->data[vec->count];
//  vec->count--;
//  return popped_value;
//}
//void array_push(array_t *arr, void *obj) {
//  if (NULL == arr) {
//    fprintf(stderr, "pushing to a NULL pointer(vector3).\n");
//    return;
//  }
//
//  if (NULL == obj) {
//    fprintf(stderr, "pushing a NULL value to a vector is not allowed.\n");
//    return;
//  }
//
//  if (arr->size== arr->count) {
//    int new_cap = vec->capacity * 2;
//    void *new_data = realloc(vec->data, new_cap * sizeof(void *));
//    if (NULL == new_data) {
//      free(vec);
//      fprintf(stderr, "Failed to allocate heap memory.\n");
//      return;
//    }
//    vec->capacity = new_cap;
//    vec->data = new_data;
//  }
//
//  vec->data[vec->count] = obj;
//  vec->count++;
//  return;
//}
