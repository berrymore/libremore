#ifndef REM_ASSERT_H
#define REM_ASSERT_H

#include <stdio.h>
#include <stdlib.h>
#include <libremore/macros.h>

REM_STATIC_IMPL
void rem_fatal(const char *name, const char *file, const int line) {
    fprintf(stderr, "FATAL ERROR %s:%d: %s is null pointer\n", file, line, name);
    abort();
}

#define ASSERT_NOT_NULL(ptr) \
    do { \
        if (!(ptr)) { \
            rem_fatal(#ptr, __FILE__, __LINE__); \
        } \
    } while (0)

#endif //REM_ASSERT_H
