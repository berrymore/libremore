#ifndef REM_IO_INL
#define REM_IO_INL

REM_STATIC_IMPL
rem_status_t rem_io_write(rem_writer_t *writer, const uint8_t *data, size_t size, size_t *written_size) {
    ASSERT_NOT_NULL(writer);
    ASSERT_NOT_NULL(data);

    return writer->write(writer, data, size, written_size);
}

#endif //REM_IO_INL
