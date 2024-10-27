#include "alloc.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void *heap[HEAP_CAP] = {0};
size_t h_size = 0;

node_t alloced_head = {{0, 1}, NULL};
node_t free_head = {{0, 1}, NULL};
node_t *alloced_chunks = &alloced_head;
node_t *free_chunks = &free_head;

void printList(node_t *head) {
    node_t *temp = head;
    while (temp != NULL) {
        printf("%p -> ", temp->chunk.strt_addr);
        temp = temp->next;
    }
    printf("NULL\n");
}

void *alloc(size_t size) {
    // add a chunk to alloced chunks
    // search free list for a chunk that fits the required space
    // remove part of that chunk
    // add the chunk to allocated list
    // return pointer to the start of the chunk
    assert(h_size + size < HEAP_CAP);

    void *alloced_addr = heap[h_size];
    h_size += size;

//    chunk_t chunk = {alloced_addr, size};
//    node_t new_allocation = {chunk, NULL};
//
//    node_t *curr = free_chunks;
//    while (curr != NULL) {
//        if (curr->chunk.size >= size) {
//        }
//    }
//
//    curr = alloced_chunks;
//    while (curr != NULL) {
//        curr = curr->next;
//    }
//
//    curr->next = &new_allocation;
//
    return ;
}

void heap_free(void *ptr) {
    // remove chunk from allocated list
    // add chunk to free list
    // perform free list collection "rearrange and combine the consecutive
    // chunks" now the dangling pointer is not our problem but how can we make
    // sure that the program crashes if the pointer is accessed again i really
    // dont know but i love this what happens when u free a pointer ? the memory
    // is returned to the heap and can be allocated so if the chunk is now in
    // the free list what keeps the user from still accessing it how will i make
    // the program crash like it does when i access a freed memory i dont get
    // this part

    TODO();
}
