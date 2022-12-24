#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int BUFF_SIZE = 3;
	int fd = open("./abc.txt", O_RDONLY);
	char buf[BUFF_SIZE];
	int read_return = 1;
	if (fd != -1)
	{
		while (read_return != 0)
		{
			read_return = read(fd, buf, BUFF_SIZE);
			printf("%s\n", buf);
		}
	}
	close(fd);
	
}
