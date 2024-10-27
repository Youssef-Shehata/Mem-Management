#include <stdio.h>

#define HEAP_CAP 640000
#define ALLOCED_SIZE 1024
#define FREE_SIZE 1024
#define MAS 8 //Minimum Allocation Bytes
#define TODO()                                                                 \
    fprintf(stderr, "%d : TODO : %s\n", __LINE__, __func__);                   \
    exit(1)


typedef struct Node node_t;
typedef struct {
    void *strt_addr;
    size_t size;
} chunk_t;

typedef struct Node {
    chunk_t chunk;
    node_t *next;
} node_t;
void printList(node_t *head);
void *alloc(size_t size);
void heap_free(void *ptr);
