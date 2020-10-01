#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if (argc != 1) {
        fprintf(2, "Please check the argument count");
    }

    // two pipes. p1: child write, parent read. p2: p1 in turn 
    int p1[2], p2[2];
    char message[1];

    // create pipe in p1, p2, p[0]:read p[1]:write
    pipe(p1);
    pipe(p2);

    int fpid = fork();
    if (fpid > 0) {
        // In parent, sent 'P' to child and get 'C' from child.
        write(p1[1], "P", 1);
        if (read(p2[0], message, 1) && 'C' ==  message[0]) {
            printf("%d: received pong\n", getpid());   
        }
        close(p2[0]);
        close(p1[1]);
    } else if (fpid == 0) {
        // In child, get 'P' from parent and sent 'C' to parent.
        if (read(p1[0], message, 1) && 'P' == message[0]) {
            printf("%d: received ping\n", getpid());
        }
        write(p2[1], "C", 1);
        close(p1[0]);
        close(p2[1]);
    } else {
        printf("Something wrong!\n");
        exit(1);
    }
    exit(0);
}
