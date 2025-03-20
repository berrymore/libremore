#ifndef REM_ALLOCATOR_H
#define REM_ALLOCATOR_H

#include <stddef.h>
#include <libremore/macros.h>

typedef struct rem_allocator rem_allocator_t;

struct rem_allocator {
    void *(*acquire)(rem_allocator_t *allocator, size_t size);

    void *(*realloc)(rem_allocator_t *allocator, void *ptr, size_t size);

    void (*release)(rem_allocator_t *allocator, void *ptr);

    void *ctx;
};

/**
 * @return Standard allocator
 */
rem_allocator_t *rem_allocator_std(void);

/**
 * @brief  Acquire a memory
 *
 * @param  allocator  The allocator
 * @param  size       An allocation size
 *
 * @return Pointer to the allocation
 */
REM_STATIC_IMPL
void *rem_mem_acquire(rem_allocator_t *allocator, size_t size);

/**
 * @brief  Reallocate a memory
 *
 * @param  allocator  The allocator
 * @param  ptr        Pointer to the previous allocation
 * @param  size       An allocation size
 *
 * @return Pointer to the new allocation
 */
REM_STATIC_IMPL
void *rem_mem_realloc(rem_allocator_t *allocator, void *ptr, size_t size);

/**
 * @brief  Release (free) a memory
 *
 * @param  allocator The allocator
 * @param  ptr       Pointer to the allocation
 */
REM_STATIC_IMPL
void rem_mem_release(rem_allocator_t *allocator, void *ptr);

#include <libremore/allocator.inl>

#endif //REM_ALLOCATOR_H
