#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t rc = fork();

    if (rc < 0) {
        // Fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // Child process
        printf("hello\n");
    } else {
        // Parent process
        // Pausing the parent for 1 second to let the child execute first
        sleep(1); 
        printf("goodbye\n");
    }

    return 0;
}

/* 
*********************************************
    Dylan Roland
   Question 3 : Can you ensure the child prints first without calling wait() in the parent?
   Answer: Yes. One simple way is to have the parent call sleep(1), forcing it to pause and giving the child process time to execute and print "hello" first. Note that while this works practically most of the time, it is not purely deterministic. For a 100% strict guarantee without wait(), you would need to use inter-process communication like pipes or signals to make the parent block until the child explicitly sends a message.
********************************************* 
*/
