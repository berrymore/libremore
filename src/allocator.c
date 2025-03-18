#include <stdlib.h>
#include <libremore/allocator.h>

// Default Allocator

static void *default_allocator_acquire(rem_allocator_t *allocator, size_t size) {
    (void) allocator;

    return malloc(size);
}

static void default_allocator_release(rem_allocator_t *allocator, void *ptr) {
    (void) allocator;
    free(ptr);
}

static rem_allocator_t default_allocator = (rem_allocator_t){
    .acquire = default_allocator_acquire,
    .release = default_allocator_release,
    .ctx = NULL,
};

rem_allocator_t *rem_allocator_default(void) {
    return &default_allocator;
}
