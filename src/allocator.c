#include <stdlib.h>
#include <libremore/allocator.h>

// Standard Allocator

static void *std_allocator_acquire(rem_allocator_t *allocator, const size_t size) {
    (void) allocator;
    return malloc(size);
}

static void *std_allocator_realloc(rem_allocator_t *allocator, void *ptr, const size_t size) {
    (void) allocator;
    return realloc(ptr, size);
}

static void std_allocator_release(rem_allocator_t *allocator, void *ptr) {
    (void) allocator;
    free(ptr);
}

static rem_allocator_t std_allocator = {
    .acquire = std_allocator_acquire,
    .realloc = std_allocator_realloc,
    .release = std_allocator_release,
    .ctx = NULL,
};

rem_allocator_t *rem_allocator_std(void) {
    return &std_allocator;
}
