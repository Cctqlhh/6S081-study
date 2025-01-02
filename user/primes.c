#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void sieve(int*);

int
main(int argc, char **argv)
{	int p[2];
	pipe(p);

	if(fork() != 0){
		close(p[0]);
		int i;
		for(i=2; i<=35; i++){
			write(p[1], &i, sizeof(i));
		}
		i = -1;
		write(p[1], &i, sizeof(i));
	}
	else{
		close(p[1]);
		sieve(p);
		exit(0);
	}
	
	wait(0);
	exit(0);
}

void sieve(int pl[2]){
	int p;
	read(pl[0], &p, sizeof(p));
	if(p == -1){
		exit(0);
	}
	printf("prime %d\n", p);

	int pr[2];
	pipe(pr);
	if(fork() != 0){
		close(pr[0]);
		int buf;
		while(read(pl[0], &buf, sizeof(buf)) && buf!= -1){
			if(buf % p != 0){
				write(pr[1], &buf, sizeof(buf));
			}
		}
		buf = -1;
		write(pr[1], &buf, sizeof(buf));
		wait(0);
		exit(0);
	}
	else{
		close(pr[1]);
		close(pl[0]);
		sieve(pr);
	}
}