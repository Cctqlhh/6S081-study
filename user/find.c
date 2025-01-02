#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int i;

    if(argc < 2){
    ls(".");
    exit(0);
    }
    for(i=1; i<argc; i++)
    ls(argv[i]);
    exit(0);
}