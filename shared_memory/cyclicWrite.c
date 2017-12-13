#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include "cyclic_buf.h"
#include "gen.h"
#include "gen.c"

int main()
{
	int fd = shm_open( "simple_memory", O_CREAT | O_RDWR, S_IRWXU );
	if( fd == -1 )
	{
		perror("open error");
		return 1;
	}

	int truncate;
	truncate = ftruncate( fd, sizeof(struct cyclic));
	if( truncate == -1 )
	{
		perror("truncate error");
		return truncate;
	}
	
	struct cyclic* memory = mmap( NULL, sizeof(struct cyclic), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
	if( memory == NULL )
	{
		perror("mmap error");
		return -1;
	}
   
    memory -> pos = 0;
    uint32_t seed = 0;
    while(1) {
		generate((void*) memory->array[memory->pos %= _BLOCK_COUNT], seed);
		printf("Generating array[%d] - seed: %d\n", memory -> pos %= _BLOCK_COUNT,seed);
		seed += 1;
		memory->pos +=1;
    }

	return 0;
}
