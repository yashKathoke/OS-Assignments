// syscalls_demo.cpp
#include <iostream>      // only for simple cout headings
#include <unistd.h>      // fork, read, write, close
#include <sys/types.h>   // pid_t
#include <sys/wait.h>    // wait
#include <fcntl.h>       // open

int main() {
    // --- FILE SYSTEM CALLS DEMO ---
    int fd = open("input.txt", O_RDONLY);
    if (fd < 0) {
        std::cout << "Failed to open file\n";
        return 1;
    }

    
    // --- PROCESS SYSTEM CALLS DEMO ---
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        write(1, "\nChild Process\n", 15);
        
        char buffer[50];
        int bytes = read(fd, buffer, sizeof(buffer));
        
        // Write to STDOUT using write()
        write(1, "Data read: ", 11);
        write(1, buffer, bytes);
        write(1, "\n", 1);

        close(fd);

    }
    else if (pid > 0) {
        // Parent waits for child
        wait(NULL);
        write(1, "Parent Process\n", 15);
    }
    else {
        std::cout << "fork failed";
    }

    return 0;
}
