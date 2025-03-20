#ifndef REM_MACROS_H
#define REM_MACROS_H

#ifndef REM_STATIC_IMPL
#   define REM_STATIC_IMPL static inline
#endif

#ifndef MIN
#   define MIN(x,y) ((x) < (y) ? (x) : (y))
#endif

#endif //REM_MACROS_H
