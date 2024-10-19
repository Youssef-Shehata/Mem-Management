#include "object.h"
#include "stack.h"
#include <stdio.h>

int main() {
    object_t *a1 = new_array(1);
    object_t *a2 = new_array(1);
    
    object_t *i1 = new_integer(1);
    object_t *i2 = new_integer(2);
    array_set(a1, 0, i1);
    array_set(a2, 0, i2);
    object_t *sum =add(a1, a2);
    for( int i =0; i< length(sum);i++){
    printf("testing add : %i" , sum->data.v_array.elements[i]->data.v_int);
  }

    printf("\n" );
  object_t *s1 = new_string("youssef");
  s1->ref_count = 2;
  refcount_free(s1);
  refcount_dec(s1);
  if (NULL == s1) {
    printf("NULLED and free correctly , hopefully ask valgrind to make sure");
  }
  return 0;
}
