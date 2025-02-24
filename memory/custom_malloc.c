#include <unistd.h>
#include <sys/mman.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define ALIGN_SIZE 8 // Align memory to 8 bytes (common for 64-bit systems)

typedef struct Block {
    size_t size;        // Size of the block, including the header
    struct Block *next; // Pointer to the next free block
} Block;

static Block *free_list = NULL; // Free list of memory blocks

// Align the size to the nearest multiple of ALIGN_SIZE
size_t align_size(size_t size) {
    return (size + ALIGN_SIZE - 1) & ~(ALIGN_SIZE - 1);
}

// Malloc function
void *my_malloc(size_t size) {
    size = align_size(size);
    
    // First, check if we have any available free blocks in the free list
    Block *prev = NULL;
    Block *curr = free_list;

    while (curr) {
        if (curr->size >= size) {
            // We have a free block that is large enough
            if (prev) {
                prev->next = curr->next;
            } else {    
                free_list = curr->next;
            }
            return (void *)(curr + 1); // Skip the block header to get to the user data
        }
        prev = curr;
        curr = curr->next;
    }

    // If no suitable block, allocate new memory using mmap
    Block *new_block = mmap(NULL, size + sizeof(Block), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (new_block == MAP_FAILED) {
        return NULL; // mmap failed
    }

    // Set the block size
    new_block->size = size;
    return (void *)(new_block + 1); // Skip the block header to get to the user data
}

// Free function
void my_free(void *ptr) {
    if (!ptr) return;
    
    Block *block = (Block *)ptr - 1; // Get the block header

    // Add the block back to the free list
    block->next = free_list;
    free_list = block;
}

// Test the allocator
int main() {
    int *ptr1 = (int *) my_malloc(sizeof(int));
    
    *ptr1 = 5;
    printf("my integer is usable: %d\n", *ptr1);
    
    my_free(ptr1);
    printf("Memory allocation and free successful!\n");
    return 0;
}
