#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Create an array to hold the read and write file descriptors for the pipe
    int fd[2];
    
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed\n");
        exit(1);
    }

    pid_t rc1 = fork();

    if (rc1 < 0) {
        fprintf(stderr, "fork 1 failed\n");
        exit(1);
    } else if (rc1 == 0) {
        // Child 1: Will write to the pipe
        close(fd[0]); // Close the read end of the pipe, as it is not needed here
        
        // Redirect standard output to the write end of the pipe
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]); // Close the original file descriptor since it's now duplicated
        
        // This print statement goes into the pipe, not to the terminal
        printf("Hello from Child 1!"); 
        exit(0);
    }

    pid_t rc2 = fork();

    if (rc2 < 0) {
        fprintf(stderr, "fork 2 failed\n");
        exit(1);
    } else if (rc2 == 0) {
        // Child 2: Will read from the pipe
        close(fd[1]); // Close the write end of the pipe, as it is not needed here
        
        // Redirect standard input to the read end of the pipe
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]); // Close the original file descriptor
        
        char buffer[100];
        // Read from standard input (which is now connected to the pipe)
        int bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0'; // Null-terminate the string
            // This print statement goes to the terminal
            printf("Child 2 received the message: %s\n", buffer);
        }
        exit(0);
    }

    // Parent process
    // The parent must close both ends of the pipe so the children don't hang waiting for it
    close(fd[0]);
    close(fd[1]);
    
    // Wait for both children to finish
    waitpid(rc1, NULL, 0);
    waitpid(rc2, NULL, 0);

    return 0;
}

/* 
*********************************************
   Dylan Roland
   Question 8: Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the pipe() system call.
   Answer: The code above implements this. By using the pipe() system call, we get two file descriptors (one for reading, one for writing). By using dup2(), we can overwrite the standard output of the first child to point to the pipe's write end, and the standard input of the second child to point to the pipe's read end. This allows seamless inter-process communication.
********************************************* 
*/
