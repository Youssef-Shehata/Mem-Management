#include "object.h"
#include "assert.h"
#include "stdbool.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include <threads.h>
#include <time.h>
object_t *_new_object() {

  object_t *obj = calloc(1, sizeof(object_t));
  if (NULL == obj) {
    fprintf(stderr, "Failed to allocate heap memory.\n");
    exit(EXIT_FAILURE);
  }
  obj->ref_count = 1;

  return obj;
}
void refcount_inc(object_t *obj) {
  if (NULL == obj)
    return;
  obj->ref_count++;
}

void refcount_dec(object_t *obj) {
  if (NULL == obj)
    return;

  obj->ref_count--;
  if (obj->ref_count == 0) {
    refcount_free(obj);
  }
}

void refcount_free(object_t *obj) {
  if (NULL == obj)
    return;
  switch (obj->kind) {
  case INTEGER:
    printf("freeing integer\n");
    break;
  case FLOAT:
    printf("freeing float\n");
    break;

  case STRING:
    printf("freeing string\n");
    free(obj->data.v_string);
    obj->data.v_string = NULL;
    break;

  case ARRAY:
    printf("freeing array\n");
    for (int i = 0; i < obj->data.v_array.size; i++) {
      refcount_dec(obj->data.v_array.elements[i]);
    }
    free(obj->data.v_array.elements);
    obj->data.v_array.elements = NULL;
    break;
  default:
    assert(false);
  }

  free(obj);
  obj = NULL;
}

object_t *new_integer(int value) {
  object_t *obj = _new_object();
  obj->data.v_int = value;
  obj->kind = INTEGER;
  return obj;
}

object_t *new_float(float value) {
  object_t *obj = _new_object();
  object_data_t n = {.v_float = value};
  object_kind_t t = FLOAT;
  obj->data = n;
  obj->kind = t;
  return obj;
}
object_t *new_string(char *value) {

  int string_length = strlen(value);
  object_t *o = (object_t *)malloc(sizeof(object_t));

  if (o == NULL) {
    fprintf(stderr, "Failed to allocate heap memory.\n");
    exit(EXIT_FAILURE);
  }

  char *ss = (char *)malloc(strlen(value) + 1);

  if (ss == NULL) {
    fprintf(stderr, "Failed to allocate heap memory.\n");
    free(o);
    exit(EXIT_FAILURE);
  }

  strcpy(ss, value);

  object_data_t data = {.v_string = ss};
  o->data = data;
  o->kind = STRING;
  return o;
}

object_t *new_array(size_t size) {

  if (size <= 0) {
    fprintf(stderr, "size must be atleast 1\n");
    exit(EXIT_FAILURE);
  }

  object_t *array_object = _new_object();

  object_t **elements = calloc(size, sizeof(object_t *));

  if (NULL == elements) {
    fprintf(stderr, "Failed to allocate heap memory.\n");
    free(array_object);
    exit(EXIT_FAILURE);
  }

  array_object->kind = ARRAY;
  array_object->data.v_array = (array_t){.size = size, .elements = elements};

  return array_object;
}

bool array_set(object_t *obj, size_t index, object_t *value) {

  if (NULL == obj) {
    fprintf(stderr, "provided obj is a null pointer.\n");
    return false;
  }
  if (obj->kind != ARRAY) {
    fprintf(stderr, "provided obj isnt an array.\n");
    return false;
  }

  if (index > obj->data.v_array.size) {
    fprintf(stderr, "out of bounds.\n");
    return false;
  }

  refcount_inc(value);
  if (NULL != array_get(obj, index)) {
    refcount_dec(obj->data.v_array.elements[index]);
  }

  obj->data.v_array.elements[index] = value;
  return true;
}

object_t *array_get(object_t *obj, size_t index) {
  if (NULL == obj) {
    fprintf(stderr, "provided obj is a null pointer.\n");
    exit(EXIT_FAILURE);
  }
  if (obj->kind != ARRAY) {
    fprintf(stderr, "provided obj isnt an array.\n");
    exit(EXIT_FAILURE);
  }

  if (index > obj->data.v_array.size) {
    fprintf(stderr, "out of bounds.\n");
    exit(EXIT_FAILURE);
  }

  return obj->data.v_array.elements[index];
}

int length(object_t *obj) {
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
    return obj->data.v_array.size;
    break;
  }

  fprintf(stderr, "Unknown type.\n");
  return -1;
}
object_t *add(object_t *a, object_t *b) {
  if (NULL == a || NULL == b) {
    free(a);
    free(b);
    fprintf(stderr, "Null Pointer Exception.\n");
    exit(EXIT_FAILURE);
  }

  if (a->kind == INTEGER) {
    switch (b->kind) {
    case INTEGER:
      return new_integer(a->data.v_int + b->data.v_int);
    case FLOAT:
      return new_float(a->data.v_int + b->data.v_float);
    default:
      fprintf(stderr, "Illegal Operation.\n");
      exit(EXIT_FAILURE);
      break;
    }
  }

  if (a->kind == FLOAT) {
    switch (b->kind) {
    case INTEGER:
      return new_float(a->data.v_float + b->data.v_int);
    case FLOAT:
      return new_float(a->data.v_float + b->data.v_float);
    default:
      fprintf(stderr, "Illegal Operation.\n");
      exit(EXIT_FAILURE);
    }
  }

  if (a->kind == STRING) {
    if (b->kind != STRING) {
      fprintf(stderr, "Illegal Operation.\n");
      exit(EXIT_FAILURE);
    }
    int length1 = strlen(a->data.v_string);
    int length2 = strlen(b->data.v_string);
    int new_length = length2 + length1 + 1;

    char *temp = calloc(new_length, sizeof(char));
    if (NULL == temp) {
      fprintf(stderr, "Failed to allocate heap memory.\n");
      exit(EXIT_FAILURE);
    }
    strcat(temp, a->data.v_string);
    strcat(temp, b->data.v_string);

    object_t *new_string_object = new_string(temp);
    free(temp);
    return new_string_object;
  }

  if (a->kind == ARRAY) {
    if (b->kind != ARRAY) {
      fprintf(stderr, "Illegal Operation.\n");
      exit(EXIT_FAILURE);
    }
    size_t a_size = (size_t)length(a);
    size_t b_size = (size_t)length(b);
    size_t size = a_size + b_size;
    object_t *new_arr = new_array(size);

    for (int i = 0; i < a_size; i++) {
      void *val = array_get(a, i);
      if (NULL == val) {
        printf("Failed to allocate heap memory.\n");
        free(new_arr);
        exit(EXIT_FAILURE);
      }
      bool res = array_set(new_arr, i, val);
      if (res == false) {
        printf("failed to set to array.\n");
        exit(EXIT_FAILURE);
      }
    }
    for (int i = 0; i < b_size; i++) {

      void *val = array_get(b, i);
      if (NULL == val) {
        printf("failed to get from array.\n");
        free(new_arr);
        exit(EXIT_FAILURE);
      }

      bool res = array_set(new_arr, i + a_size, val);
      if (res == false) {
        printf("failed to set to array.\n");
        exit(EXIT_FAILURE);
      }
    }
    return new_arr;
  }

  fprintf(stderr, "Uknown type.\n");
  exit(EXIT_FAILURE);
}
