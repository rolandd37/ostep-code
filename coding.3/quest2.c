#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // Open a file before calling fork()
    // O_CREAT creates it if it doesn't exist, O_WRONLY is write-only, O_TRUNC clears existing contents
    int fd = open("quest2_output.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    
    if (fd < 0) {
        fprintf(stderr, "File open failed\n");
        exit(1);
    }

    pid_t rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // Child process
        const char *child_msg = "Child process writing to the file.\n";
        write(fd, child_msg, strlen(child_msg));
    } else {
        // Parent process
        const char *parent_msg = "Parent process writing to the file.\n";
        write(fd, parent_msg, strlen(parent_msg));
        
        // Wait for child to finish
        wait(NULL); 
    }

    // Both processes close the file descriptor when they are done
    close(fd);
    return 0;
}

/* 
*********************************************
   Dylan Roland
   Question 1: Can both the child and parent access the file descriptor returned by open()? 
   Answer: Yes. When fork() is called, the child process receives an exact copy of the parent's file descriptor table. This means both processes have a file descriptor pointing to the exact same open file.
   
   Question 2: What happens when they are writing to the file concurrently, i.e., at the same time?
   Answer: Both processes can write to the file without crashing. Because they share the same open file description, they also share the file offset pointer. This means their outputs will be appended one after the other rather than overwriting each other. However, the exact order of the lines in the file is non-deterministic and depends on the operating system's scheduler.
********************************************* 
*/
