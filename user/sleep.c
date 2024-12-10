#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(2, "please input sleep time\n");
		exit(0);
	}

	int i;
	i = atoi(argv[1]);
	sleep(i);
	exit(0);	
}
