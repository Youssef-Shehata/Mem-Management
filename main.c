#include "object.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "assert.h"
#include "alloc.h"
int main(){
    int *i = (int *)alloc(sizeof(int));
    int *x = malloc(sizeof(int));
    *i = 5;
    printf("%d",*i);


    
  return 0;
}
