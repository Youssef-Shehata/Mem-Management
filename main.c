#include "object.h"
#include "stack.h"
#include <stdio.h>

int main() {
  object_t *obj1 = new_snek_array(2);
  if(NULL == obj1){
      return 1;
  }
  object_t *obj2 = new_snek_array(2);
  if(NULL == obj2){
      return 1;
  }

  object_t *one = new_integer(1);
  if(NULL == one){
      return 1;
  }
  object_t *two = new_integer(2);
  if(NULL == two){
      return 1;
  }
  object_t *three = new_integer(3);
  if(NULL == three){
      return 1;
  }
  object_t *four = new_integer(4);
  if(NULL == four){
      return 1;
  }
  snek_array_set(obj1, 0, one);
  snek_array_set(obj1, 1, two);

  snek_array_set(obj2, 0, three);
  snek_array_set(obj2, 1, four);
  object_t *sum = snek_add(obj1, obj2);
  if (NULL == sum) {
    printf("sun returned null.\n");
    return 0;
  }

  for (int i = 0; i < sum->data.v_array->size; i++) {
    object_t *integer = sum->data.v_array->elements[i];

    printf("%i \n", integer->data.v_int);
  }

  return 0;
}
