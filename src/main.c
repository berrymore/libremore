#include <stdlib.h>

#include <libremore/allocator.h>

int main(void) {
    rem_allocator_t *allocator = rem_allocator_std();

    const size_t size = 128;
    char *buffer = rem_mem_acquire(allocator, size);

    if (!buffer) {
        fprintf(stderr, "Failed to allocate %zu bytes\n", size);
        return EXIT_FAILURE;
    }

    snprintf(buffer, size, "Hello, allocator!");
    printf("%s\n", buffer);

    rem_mem_release(allocator, buffer);

    return EXIT_SUCCESS;
}
