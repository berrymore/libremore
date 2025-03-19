#include <stdlib.h>
#include <libremore/allocator.h>

// Default Allocator

static void *std_allocator_acquire(rem_allocator_t *allocator, size_t size) {
    (void) allocator;

    return malloc(size);
}

static void std_allocator_release(rem_allocator_t *allocator, void *ptr) {
    (void) allocator;
    free(ptr);
}

static rem_allocator_t std_allocator = (rem_allocator_t){
    .acquire = std_allocator_acquire,
    .release = std_allocator_release,
    .ctx = NULL,
};

rem_allocator_t *rem_allocator_std(void) {
    return &std_allocator;
}
