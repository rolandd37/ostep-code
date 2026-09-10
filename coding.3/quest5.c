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
        
        // Trying to call wait() in the child
        pid_t child_wait_rc = wait(NULL);
        printf("Child process wait() returned: %d\n", child_wait_rc);
    } else {
        // Parent process
        printf("Parent process waiting for child (PID: %d)...\n", rc);
        
        // Calling wait() in the parent
        pid_t parent_wait_rc = wait(NULL);
        printf("Parent process wait() returned: %d\n", parent_wait_rc);
    }

    return 0;
}

/* 
*********************************************
   Dylan Roland
   Question 5: What does wait() return? What happens if you use wait() in the child?
   Answer: In the parent, wait() returns the process ID (PID) of the terminated child process. If you use wait() in the child process (assuming the child has not created any children of its own), it returns -1 immediately, indicating that there are no child processes to wait for.
********************************************* 
*/
