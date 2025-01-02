#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{	
	char buff[4];
	int p1[2], p2[2];
	pipe(p1);
	pipe(p2);
	if(fork() == 0)
	{
		close(p1[1]);
		close(p2[0]);

		read(p1[0], buff, 4);
		// close(p1[0]);
		printf("%d: received %s\n", getpid(), buff);
		write(p2[1], "pong", 4);
		// close(p2[1]);
		exit(0);
	}
	else{
		close(p1[0]);
		close(p2[1]);
		write(p1[1], "ping", 4);
		// close(p1[1]);
		read(p2[0], buff, 4);
		// close(p2[0]);
		printf("%d: received %s\n", getpid(), buff);
		wait(0);
	}
	exit(0);
}
