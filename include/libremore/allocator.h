#ifndef REM_ALLOCATOR_H
#define REM_ALLOCATOR_H

#include <stdio.h>
#include <libremore/macros.h>

/**
 * @brief An allocator type
 */
typedef struct rem_allocator rem_allocator_t;

/**
 * @brief  Function pointer for acquire implementation
 *
 * @param  allocator The allocator
 * @param  size      The size of an acquired memory
 *
 * @return Pointer to the allocation
 */
typedef void *(*rem_mem_acquire_fn)(rem_allocator_t *allocator, size_t size);

/**
 * @brief  Function pointer for release implementation
 *
 * @param  allocator The allocator
 * @param  ptr       The pointer to the memory
 */
typedef void (*rem_mem_release_fn)(rem_allocator_t *allocator, void *ptr);

/**
 * @brief An allocator interface
 */
struct rem_allocator {
    rem_mem_acquire_fn acquire;
    rem_mem_release_fn release;
    void *ctx;
};

/**
 * @return The standard allocator
 */
rem_allocator_t *rem_allocator_std(void);

/**
 * @brief  Inline wrapper for memory acquiring through the allocator
 * @param  allocator  The allocator
 * @param  size       The size of acquired memory
 * @return The pointer to the memory
 */
REM_STATIC_IMPL
void *rem_mem_acquire(rem_allocator_t *allocator, size_t size);

/**
 * @brief  Inline impl for memory releasing through the allocator
 * @param  allocator The allocator
 * @param  ptr       The pointer
 */
REM_STATIC_IMPL
void rem_mem_release(rem_allocator_t *allocator, void *ptr);

//
// Inline implementations
//

REM_STATIC_IMPL
void *rem_mem_acquire(rem_allocator_t *allocator, const size_t size) {
    if (!allocator || !allocator->acquire || size < 1) {
        return NULL;
    }

    return allocator->acquire(allocator, size);
}

REM_STATIC_IMPL
void rem_mem_release(rem_allocator_t *allocator, void *ptr) {
    if (!allocator || !allocator->release) {
        perror("Cannot release NULL");
        return;
    }

    allocator->release(allocator, ptr);
}

#endif //REM_ALLOCATOR_H
