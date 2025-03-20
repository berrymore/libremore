#ifndef REM_STATUS_H
#define REM_STATUS_H

typedef enum {
    REM_OK = 0,
    REM_ALLOC_FAILED = 1,
} rem_status_t;

#define REM_SUCCESS(status) ((status) == REM_OK)

#endif //REM_STATUS_H
