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
        
        // Close standard output
        close(STDOUT_FILENO);
        
        // Try to print something after closing stdout
        printf("Child process: You will not see this print statement.\n");
        
    } else {
        // Parent process
        wait(NULL); 
        printf("Parent process: execution finished.\n");
    }

    return 0;
}

/* 
*********************************************
    Dylan Roland
   Question 7: What happens if the child calls printf() to print some output after closing the descriptor?
   Answer: The output from the child's printf() will not appear on the terminal. The printf() function fundamentally relies on writing to standard output (file descriptor 1). Because we closed STDOUT_FILENO, the underlying write() system call that printf() depends on fails, and the text simply vanishes into the void.
********************************************* 
*/
