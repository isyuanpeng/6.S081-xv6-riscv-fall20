// Simple sleep in system call 'sleep'.

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[])
{
    // first judge the number of params. if wrong, write to error output fd:2.
    if (argc < 2) {
        fprintf(2, "Please check the argument count!\n");
        exit(1);
    }

    // the sleep(argv[1]) argv[0] = 'sleep' argv[1] = ticks
    int ticks;
    ticks = atoi(argv[1]);
    if (ticks < 0) {
        fprintf(2, "Something error!\n");
        exit(1);
    }
    sleep(ticks);
    exit(0); 
}
