#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // Child process
        printf("Child process (PID: %d) executing.\n", getpid());
    } else {
        // Parent process
        printf("Parent process waiting for specific child (PID: %d)...\n", rc);
        
        // Calling waitpid() instead of wait()
        // The first argument is the specific PID to wait for
        pid_t wait_rc = waitpid(rc, NULL, 0);
        printf("Parent process waitpid() returned: %d\n", wait_rc);
    }

    return 0;
}

/* 
*********************************************
    Dylan Roland
   Question 6: When would waitpid() be useful?
   Answer: waitpid() is particularly useful when a parent process creates multiple child processes and needs to wait for one specific child to finish, rather than just the first one that happens to terminate. It also offers advanced options, such as WNOHANG, which allows the parent to check if a child has finished without blocking its own execution.
********************************************* 
*/
