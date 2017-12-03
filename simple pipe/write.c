#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);
		int i = 0;
		 fd = open(myfifo, O_WRONLY);
   		 		write(fd, "Simple pipe no imagination for more", sizeof("Simple pipe no imagination for more"));	
		 close(fd);
		

    unlink(myfifo);

    return 0;
}
