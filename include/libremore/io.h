#ifndef REM_IO_H
#define REM_IO_H

#include <stdint.h>
#include <libremore/macros.h>
#include <libremore/status.h>


typedef struct rem_writer rem_writer_t;

struct rem_writer {
    rem_status_t (*write)(rem_writer_t *writer, const uint8_t *data, size_t size, size_t *written_size);

    void *ctx;
};

/**
 * @brief  Write `size` bytes of `data` into writer
 *
 * @param  writer        The writer
 * @param  data          A source of data
 * @param  size          Length
 * @param  written_size  Count of written bytes
 *
 * @return Result status
 */
REM_STATIC_IMPL
rem_status_t rem_io_write(rem_writer_t *writer, const uint8_t *data, size_t size, size_t *written_size);

#include <libremore/io.inl>

#endif //REM_IO_H
