#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>
#include <stdio.h>

/**
 * @brief The abstract allocator type
 */
typedef struct rem_allocator rem_allocator_t;

/**
 * @brief  Function pointer for acquire implementation
 * @param  allocator The allocator
 * @param  size      The size of an acquired memory
 * @return Pointer that points to the allocation
 */
typedef void *(*rem_mem_acquire_fn)(rem_allocator_t *allocator, size_t size);

/**
 * @brief  Function pointer for release implementation
 * @param  allocator The allocator
 * @param  ptr       The pointer to the memory
 * @return Nothing
 */
typedef void (*rem_mem_release_fn)(rem_allocator_t *allocator, void *ptr);

/**
 * @brief The allocator interface
 */
struct rem_allocator {
    rem_mem_acquire_fn acquire;
    rem_mem_release_fn release;
    void *ctx;
};

static inline void *rem_mem_acquire(rem_allocator_t *allocator, size_t size) {
    if (!allocator || !allocator->acquire) {
        return NULL;
    }

    return allocator->acquire(allocator, size);
}

static inline void rem_mem_release(rem_allocator_t *allocator, void *ptr) {
    if (!allocator || !allocator->release) {
        perror("Cannot release NULL");
        return;
    }

    allocator->release(allocator, ptr);
}

// Default Allocator

/**
 * @return The default allocator
 */
rem_allocator_t *rem_allocator_default(void);

#endif //ALLOCATOR_H
