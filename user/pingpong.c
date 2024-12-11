#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{	
	char buff[2];
	buff[0] = 't';
	int p[2];
	pipe(p);
	write(p[1], buff, 1);
	close(p[1]);

	if(fork() == 0)
	{
		read(p[0], buff+1, 1);
		close(p[0]);
		printf("%d: received ping\n", getpid());
		write(p[1], buff, 1);
		close(p[1]);
		exit(0);
	}
	sleep(1);
	read(p[0], buff+1, 1);
	close(p[0]);
	printf("%d: received pong\n", getpid());
	exit(0);
}
