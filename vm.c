#include "vm.h"
#include <stdio.h>
#include <stdlib.h>


vm_t *vm_new(){
    vm_t *vm = malloc(sizeof(vm_t));
    if( NULL == vm){
        fprintf(stderr, "failed to allocate heap memory.\n");
        return NULL;
    }

    vm->objects =stack_new(8);
    vm->frames=stack_new(8);


    return vm;


}
void vm_free(vm_t *vm){
    stack_free(vm->frames);
    stack_free(vm->objects);
    free(vm);
}
