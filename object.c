#include "object.h"
#include "stdbool.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include <threads.h>
#include <time.h>
object_t *new_integer(int value) {
  object_t *obj = (object_t *)malloc(sizeof(object_t));
  if (obj == NULL) {
    fprintf(stderr, "Failed to allocate heap memory.\n");
    return NULL;
  }
  obj->data.v_int = value;
  obj->kind = INTEGER;
  return obj;
}

object_t *new_float(float value) {
  object_t *obj = (object_t *)malloc(sizeof(object_t));
  if (obj == NULL) {
    fprintf(stderr, "Failed to allocate heap memory.\n");
    return NULL;
  }
  object_data_t n = {.v_float = value};
  object_kind_t t = FLOAT;
  obj->data = n;
  obj->kind = t;
  return obj;
}
object_t *new_string(char *value) {

  int string_length = strlen(value);
  if (string_length == 0) {
    fprintf(stderr, "Provided string is empty.\n");
    return NULL;
  }
  object_t *o = (object_t *)malloc(sizeof(object_t));

  if (o == NULL) {
    fprintf(stderr, "Failed to allocate heap memory.\n");
    return NULL;
  }

  char *ss = (char *)malloc(strlen(value) + 1);

  if (ss == NULL) {
    fprintf(stderr, "Failed to allocate heap memory.\n");
    free(o);
    return NULL;
  }

  strcpy(ss, value);

  object_data_t data = {.v_string = ss};
  o->data = data;
  o->kind = STRING;
  return o;
}

object_t *new_snek_array(size_t size) {
  if (size == 0) {
    return NULL;
  }

  object_t *array_object = (object_t *)malloc(sizeof(object_t));
  if (NULL == array_object) {
    fprintf(stderr, "Failed to allocate heap memory for array.\n");
    return NULL;
  }
  array_t *array = new_array(size);
  if (NULL == array) {
    fprintf(stderr, "Failed to allocate heap memory for elements of array.\n");
    free(array_object);
    return NULL;
  }
  array_object->kind = ARRAY;
  object_data_t data = {.v_array = array};
  array_object->data = data;

  return array_object;
}

bool snek_array_set(object_t *snek_obj, size_t index, object_t *value) {

  if (NULL == snek_obj) {
    fprintf(stderr, "provided obj is a null pointer.\n");
    return false;
  }
  if (snek_obj->kind != ARRAY) {
    fprintf(stderr, "provided obj isnt an array.\n");
    return false;
  }

  if (index > snek_obj->data.v_array->size) {
    fprintf(stderr, "out of bounds.\n");
    return false;
  }

  snek_obj->data.v_array->elements[index] = value;

  return true;
}

object_t *snek_array_get(object_t *snek_obj, size_t index) {

  if (NULL == snek_obj) {
    fprintf(stderr, "provided obj is a null pointer.\n");
    return NULL;
  }
  if (snek_obj->kind != ARRAY) {
    fprintf(stderr, "provided obj isnt an array.\n");
    return NULL;
  }

  if (index > snek_obj->data.v_array->size) {
    fprintf(stderr, "out of bounds.\n");
    return NULL;
  }

  printf("debugging get from array at index %li and it has the value : %p .\n",
         index, snek_obj->data.v_array->elements[index]);
  return snek_obj->data.v_array->elements[index];
}

int snek_length(object_t *obj) {
  if (NULL == obj) {
    fprintf(stderr, "Null pointer exception.\n");
    return -1;
  }

  switch (obj->kind) {
  case INTEGER:
    return 1;
  case FLOAT:
    return 1;
  case STRING:
    return strlen(obj->data.v_string);
  case ARRAY:
    return obj->data.v_array->size;
    break;
  }

  fprintf(stderr, "Unknown type.\n");
  return -1;
}
object_t *snek_add(object_t *a, object_t *b) {
  if (NULL == a || NULL == b) {
    free(a);
    free(b);
    fprintf(stderr, "Null Pointer Exception.\n");
    return NULL;
  }

  object_t *sum;

  if (a->kind == INTEGER) {
    switch (b->kind) {
    case INTEGER:
      sum = new_integer(a->data.v_int + b->data.v_int);
      return sum;
    case FLOAT:
      sum = new_float(a->data.v_int + b->data.v_float);
      return sum;
    default:
      fprintf(stderr, "Illegal Operation.\n");
      free(a);
      free(sum);
      free(b);
      return NULL;
      break;
    }
  }

  if (a->kind == FLOAT) {
    switch (b->kind) {
    case INTEGER:
      sum = new_float(a->data.v_float + b->data.v_int);
      return sum;
    case FLOAT:
      sum = new_float(a->data.v_float + b->data.v_float);
      return sum;
    default:
      fprintf(stderr, "Illegal Operation.\n");
      free(sum);
      free(a);
      free(b);
      return NULL;
    }
  }

  // TODO : implement adding 2 astrings 2 arrays and 2 vectors
  if (a->kind == STRING) {
    if (b->kind != STRING) {
      free(sum);
      free(a);
      free(b);
      fprintf(stderr, "Illegal Operation.\n");
      return NULL;
    }
    int length1 = strlen(a->data.v_string);
    int length2 = strlen(b->data.v_string);
    int new_length = length2 + length1 + 1;

    char *temp = calloc(new_length, sizeof(char));
    if (NULL == temp) {
      fprintf(stderr, "failed to allocate memory.\n");
      return NULL;
    }

    object_t *new_string_object = malloc(sizeof(object_t));
    if (NULL == new_string_object) {
      fprintf(stderr, "failed to allocate memory.\n");
      free(temp);
      return NULL;
    }
    strcat(temp, a->data.v_string);
    strcat(temp, b->data.v_string);
    new_string_object->kind = STRING;
    new_string_object->data.v_string = temp;
    return new_string_object;
  }

  if (a->kind == ARRAY) {
    if (b->kind != ARRAY) {
      fprintf(stderr, "Illegal Operation.\n");
      free(sum);
      return NULL;
    }
    int size = (a->data.v_array->size + b->data.v_array->size);
    object_t *new_arr = new_snek_array(size);
    int index = 0;
    for (int i = 0; i < a->data.v_array->size; i++) {
      void *val = snek_array_get(a, i);
      if (NULL == val) {
        printf("failed to get from array a .\n");
        free(new_arr);
        return NULL;
      }
      bool res = snek_array_set(new_arr, index, val);
      index++;
      if (res == false) {

        printf("failed to set to array  .\n");
        return NULL;
      }
    }
    printf("size of b = %li .\n", b->data.v_array->size);
    for (int i = 0;i < b->data.v_array->size; i++) {

      void *val = snek_array_get(b, i);
      if (NULL == val) {
        printf("failed to get from array b .\n");
        free(new_arr);
        return NULL;
      }



      bool res = snek_array_set(new_arr, index, val);
      index++;
      if (res == false) {
        printf("failed to set to array  .\n");
    free(a);
    free(b);
        return NULL;
      }
    }
    return new_arr;
  }

  fprintf(stderr, "Uknown type.\n");
  return NULL;
}
