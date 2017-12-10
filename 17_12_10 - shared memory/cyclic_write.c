#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>

#include "gen.h"
#include "cyclic_buf.h"

int main()
{
	int fd = shm_open( "simple_memory", O_CREAT | O_RDWR, S_IRWXU );
	if( fd < 0 )
	{
		perror("open error");
		return 1;
	}

	int truncate;
	truncate = ftruncate( fd, sizeof(struct cyclic));
	if( truncate < 0 )
	{
		perror("truncate error");
		return 2;
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
		generate((void*) memory->array[memory->pos], seed);
		printf("Generating array[%d] - seed: %d\n", memory -> pos,seed);
		seed += 1;
		memory->pos +=1;
		memory->pos %= _BLOCK_COUNT;
    }

	return 0;
}
