#include <libremore/allocator.h>
#include <libremore/assert.h>
#include <libremore/buffer.h>
#include <libremore/io.h>

int main(void) {
    rem_allocator_t *allocator = rem_allocator_std();

    rem_buffer_t buf;

    if (!REM_SUCCESS(rem_buffer_init(allocator, &buf, 0))) {
        fprintf(stderr, "rem_buffer_init() failed\n");
        return EXIT_FAILURE;
    }

    rem_writer_t buf_writer = rem_buffer_writer_new(&buf);

    rem_io_write(&buf_writer, (uint8_t *) &"Hello world!", 13, NULL);

    const char buf2[13] = {0};

    rem_buffer_read(&buf, (uint8_t *) buf2, 13);
    rem_buffer_cleanup(&buf);

    printf("Buffer: %s\n", buf2);

    return EXIT_SUCCESS;
}
