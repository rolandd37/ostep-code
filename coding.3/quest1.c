#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int x = 100;
    printf("Initial state: x is %d\n", x);

    pid_t rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("Child process: initial value of x is %d\n", x);
        x = 200;
        printf("Child process: changed value of x to %d\n", x);
    } else {
        printf("Parent process: initial value of x is %d\n", x);
        x = 300;
        printf("Parent process: changed value of x to %d\n", x);
        wait(NULL); 
    }

    return 0;
}

/* 
*********************************************
   Your name: Dylan Roland
   Question 1: What value is the variable in the child process? 
   Answer: The value of the variable in the child process is 100. The child receives an exact copy of the parent's memory space at the time of the fork.
   
   Question 2: What happens to the variable when both the child and parent change the value of x?
   Answer: When they change the value of x, they are modifying their own private, independent copies of the variable. Changing x in the child to 200 does not affect the parent's x, and changing x in the parent to 300 does not affect the child's x.
********************************************* 
*/
