#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>

#include "gen.h"
#include "gen.c"
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
    uint64_t seed;
    uint64_t seed_verify;
    int i = 0;
	printf("starting at %ld\n", position);
    while(1) {
        while (memory -> pos != position) {
		printf ("??");
		seed = verify((void *)memory -> array[position %= _BLOCK_COUNT]);
		if (seed < 0) {
			printf ("Verify error\n");
		}

		if (memory -> pos >= position + _BLOCK_COUNT) {
			printf ("neshto");
			return 2;
		}
		
		if (i == 0) {
			printf("done\n");
			seed_verify = seed;
			i = 1;
		} else if (seed_verify + 1 != seed) {
			printf ("seed error\n");
			return 3;
		} else {
			seed_verify ++;
		}
	}
        printf("Verifying array[%ld] - seed: %ld\n",position %= _BLOCK_COUNT,seed);
        position += 1;
    }
	return 0;
}
