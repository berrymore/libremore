#ifndef REM_BUFFER_H
#define REM_BUFFER_H

#include <libremore/macros.h>
#include <libremore/status.h>
#include <libremore/allocator.h>
#include <libremore/io.h>

typedef struct rem_buffer rem_buffer_t;

struct rem_buffer {
    size_t len;
    size_t capacity;
    size_t cursor;
    uint8_t *data;
    rem_allocator_t *allocator;
};

/**
 * @brief  Initialize a buffer
 *
 * @param  allocator  The allocator
 * @param  buffer     The buffer
 * @param  capacity   A buffer capacity
 *
 * @return Result status
 */
REM_STATIC_IMPL
rem_status_t rem_buffer_init(rem_allocator_t *allocator, rem_buffer_t *buffer, size_t capacity);

/**
 * @brief  Reads `len` bytes from buffer to `dst`
 *
 * @param  buffer  The buffer
 * @param  dst     The destination
 * @param  len     Length
 *
 * @return Count of read bytes
 */
REM_STATIC_IMPL
size_t rem_buffer_read(rem_buffer_t *buffer, uint8_t *dst, size_t len);

/**
 * @brief  Writes `len` bytes from `data` to buffer
 *
 * @param  buffer  The buffer
 * @param  data    A source of bytes
 * @param  len     Length
 *
 * @return Count of written bytes
 */
REM_STATIC_IMPL
size_t rem_buffer_write(rem_buffer_t *buffer, const void *data, size_t len);

/**
 * @brief  Clean up buffer
 *
 * @param  buffer  The buffer
 */
REM_STATIC_IMPL
void rem_buffer_cleanup(rem_buffer_t *buffer);

REM_STATIC_IMPL
rem_status_t rem_buffer_writer_write(rem_writer_t *writer, const uint8_t *data, const size_t len, size_t *written_size);

REM_STATIC_IMPL
rem_writer_t rem_buffer_writer_new(rem_buffer_t *buffer);

#include <libremore/buffer.inl>

#endif //REM_BUFFER_H
