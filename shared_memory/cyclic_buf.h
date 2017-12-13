#ifndef _DUMP_SHM_STRUCT
#define _DUMP_SHM_STRUCT
#define _BLOCK_SIZE 4096
#define _BLOCK_COUNT 8192

#include <stdint.h>

struct cyclic{
    volatile uint64_t pos;
    volatile int array[_BLOCK_COUNT][_BLOCK_SIZE];
};

#endif
