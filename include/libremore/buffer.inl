#ifndef REM_BUFFER_INL
#define REM_BUFFER_INL

#include <string.h>
#include <libremore/assert.h>
#include <libremore/allocator.h>

REM_STATIC_IMPL
rem_status_t rem_buffer_init(rem_allocator_t *allocator, rem_buffer_t *buffer, const size_t capacity) {
    ASSERT_NOT_NULL(allocator);
    ASSERT_NOT_NULL(buffer);

    if (capacity > 0) {
        buffer->data = rem_mem_acquire(allocator, capacity);

        if (!buffer->data) {
            fprintf(stderr, "rem_mem_acquire failed on buffer\n");
            return REM_ALLOC_FAILED;
        }
    }

    buffer->allocator = allocator;
    buffer->capacity = capacity;
    buffer->len = 0;
    buffer->cursor = 0;

    return REM_OK;
}

REM_STATIC_IMPL
void rem_buffer_cleanup(rem_buffer_t *buffer) {
    ASSERT_NOT_NULL(buffer);

    rem_mem_release(buffer->allocator, buffer->data);

    buffer->data = NULL;
    buffer->len = 0;
    buffer->cursor = 0;
    buffer->capacity = 0;
    buffer->allocator = NULL;
}

REM_STATIC_IMPL
size_t rem_buffer_read(rem_buffer_t *buffer, uint8_t *dst, const size_t len) {
    ASSERT_NOT_NULL(buffer);
    ASSERT_NOT_NULL(dst);

    if (buffer->cursor >= buffer->len) {
        return 0;
    }

    const size_t till_end = buffer->len - buffer->cursor;
    const size_t new_len = MIN(till_end, len);

    memcpy(dst, buffer->data + buffer->cursor, new_len);
    buffer->cursor += new_len;
    return new_len;
}

REM_STATIC_IMPL
size_t rem_buffer_write(rem_buffer_t *buffer, const void *data, const size_t len) {
    ASSERT_NOT_NULL(buffer);
    ASSERT_NOT_NULL(data);

    if (len == 0) {
        return 0;
    }

    if (len > buffer->capacity - buffer->len) {
        // reallocate buffer data
        size_t new_capacity = buffer->capacity * 2;
        if (new_capacity < buffer->len + len) {
            new_capacity = buffer->len + len;
        }

        uint8_t *new_data = rem_mem_realloc(buffer->allocator, buffer->data, new_capacity);
        if (!new_data) {
            return 0;
        }

        buffer->data = new_data;
        buffer->capacity = new_capacity;
    }

    memcpy(buffer->data + buffer->len, data, len);
    buffer->len += len;

    return len;
}

// io
REM_STATIC_IMPL
rem_status_t rem_buffer_writer_write(rem_writer_t *writer, const uint8_t *data, const size_t len,
                                     size_t *written_size) {
    ASSERT_NOT_NULL(writer);
    ASSERT_NOT_NULL(data);

    rem_buffer_t *buffer = writer->ctx;
    ASSERT_NOT_NULL(buffer);

    size_t written = 0;
    written = rem_buffer_write(buffer, data, len);

    if (written_size != NULL) {
        *written_size = written;
    }

    return REM_OK;
}

REM_STATIC_IMPL
rem_writer_t rem_buffer_writer_new(rem_buffer_t *buffer) {
    ASSERT_NOT_NULL(buffer);

    return (rem_writer_t){
        .write = rem_buffer_writer_write,
        .ctx = buffer,
    };
}

#endif //REM_BUFFER_INL
