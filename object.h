#include <stdio.h>
#include "stdbool.h"
typedef struct Object object_t;

typedef enum Objectkind {
  INTEGER,
  FLOAT,
  STRING,
  ARRAY,
} object_kind_t;


typedef struct Array {
    size_t size ;
    object_t**elements ;
} array_t;

typedef union ObjectData {
    int v_int;
    float v_float;
    char * v_string;
    array_t* v_array;

} object_data_t;
typedef struct Object {
    object_kind_t kind;
    object_data_t data;
} object_t;






object_t *new_integer(int value);
object_t *new_float(float value);
object_t *new_string(char* value);
object_t *new_snek_array(size_t size);


//array
array_t*new_array(size_t size);
void *array_pop(array_t* arr);
void *array_push(array_t*arr, void *obj);
bool snek_array_set(object_t*snek_obj, size_t index, object_t*value) ;
object_t*snek_array_get(object_t*snek_obj, size_t index) ;
int snek_length(object_t*obj);
object_t*snek_add(object_t*a, object_t*b) ;


