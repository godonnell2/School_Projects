#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <errno.h>
#include <string.h>

// Toggle debug mode
#define DEBUG_MODE 0

#if DEBUG_MODE

// Standard debug print to stderr
#define DEBUG_PRINTF(...) \
    fprintf(stderr, "[DEBUG] " __VA_ARGS__)

// Debug print with source location info
#define DEBUG_LOG(...) \
    fprintf(stderr, "[%d][%s:%d] ", getpid(), __FILE__, __LINE__), fprintf(stderr, __VA_ARGS__)

// Debug perror (prints strerror of errno)
#define DEBUG_PERROR(msg) \
    fprintf(stderr, "[%s:%d] ", __FILE__, __LINE__), perror(msg)

#else

#define DEBUG_PRINTF(...) ((void)0)
#define DEBUG_LOG(...) ((void)0)
#define DEBUG_PERROR(msg) ((void)0)

#endif

#endif
