#ifndef REM_ALLOCATOR_INL
#define REM_ALLOCATOR_INL

#include <libremore/allocator.h>
#include <libremore/assert.h>

REM_STATIC_IMPL
void *rem_mem_acquire(rem_allocator_t *allocator, const size_t size) {
    ASSERT_NOT_NULL(allocator);
    ASSERT_NOT_NULL(allocator->acquire);

    if (!size) {
        return NULL;
    }

    return allocator->acquire(allocator, size);
}

REM_STATIC_IMPL
void *rem_mem_realloc(rem_allocator_t *allocator, void *ptr, const size_t size) {
    ASSERT_NOT_NULL(allocator);
    ASSERT_NOT_NULL(allocator->realloc);

    if (!size) {
        return NULL;
    }

    return allocator->realloc(allocator, ptr, size);
}

REM_STATIC_IMPL
void rem_mem_release(rem_allocator_t *allocator, void *ptr) {
    ASSERT_NOT_NULL(allocator);
    ASSERT_NOT_NULL(allocator->release);

    allocator->release(allocator, ptr);
}

#endif //REM_ALLOCATOR_INL
