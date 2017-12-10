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
	int fd = shm_open( "simple_memory", O_RDONLY, 0);
	if( fd < 0 )
	{
		perror("open error");
		return 1;
	}

	struct cyclic* memory = mmap( NULL, sizeof(struct cyclic), PROT_READ, MAP_SHARED, fd, 0 );
	if( memory == NULL )
	{
		perror("mmap error");
		return -1;
	}
    
    uint64_t position = memory -> pos;
    uint32_t seed;
	printf("starting at %ld\n", position);
    while(1) {
        if (memory -> pos == position) continue;
        printf("Verifying array[%ld] - seed: %ld\n",position,verify((void *) memory -> array [position]));
        position += 1;
        position %= _BLOCK_COUNT;
    }
	return 0;
}
