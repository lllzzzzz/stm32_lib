#ifndef _LZ_DEBUG_H
#define _LZ_DEBUG_H

#include "stdio.h"

#define PRINT(fmt, args...)  \
    do                       \
    {                        \
        printf(fmt, ##args); \
    } while (0);

#define PRINT_INFO(fmt, args...)                   \
    do                                             \
    {                                              \
        printf("(info) > ");                       \
        printf(fmt, ##args);                       \
    } while (0);

#define PRINT_ERR(fmt, args...)                    \
    do                                             \
    {                                              \
        printf("{%s, %d} > ", __FILE__, __LINE__); \
        printf("[%s] > ", __func__);               \
        printf("(err) > ");                        \
        printf(fmt, ##args);                       \
    } while (0);

#endif
