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
        // Child process calls exec
        // Variant 1: execl (takes a list of arguments, requires full path)
        execl("/bin/ls", "ls", NULL);
        
        // Other variants you could try (commented out):
        // char *args[] = {"ls", NULL};
        // execvp("ls", args); // Vector of arguments, searches PATH
        
        // execlp("ls", "ls", NULL); // List of arguments, searches PATH
    } else {
        // Parent process
        wait(NULL); 
    }

    return 0;
}

/* 
*********************************************
   Dylan Roland
   Question 4: Why do you think there are so many variants of the same basic call?
   Answer: The different variants exist to provide convenience depending on how the programmer has the data structured. The letters in the function names indicate how they handle arguments: 'l' means it takes a variable-length list of arguments, 'v' means it takes an array (vector) of arguments, 'p' means it will automatically search the PATH environment variable for the executable, and 'e' means it allows you to pass a custom environment array. This flexibility prevents the programmer from having to manually format arrays or search paths themselves.
********************************************* 
*/
