#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BUF 1024

int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";
    char buf[MAX_BUF];

	int i = 0;
	write(STDOUT_FILENO, "\nSo charming I almost deserve a 4 :D\n\n", sizeof("\nSo charming i almost deserve a 4 :D\n\n"));	
	for (; i < 10; i++) {
	    fd = open(myfifo, O_RDONLY);
	    read(fd, buf, MAX_BUF);
	    printf("message %d: %s\n",i+1, buf);
	    close(fd);
	}


    return 0;
}
