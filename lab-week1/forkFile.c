//Name: Shashank
//Regno: 230970004
//date: 25-07-2024

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    char filename[100];
    char buffer[11]; 
    pid_t pid;

    printf("Enter the file name: ");
    scanf("%s", filename);

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        int fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("Error opening file in child process");
            return 1;
        }

        ssize_t bytesRead = read(fd, buffer, 10);
        if (bytesRead == -1) {
            perror("Error reading file in child process");
            close(fd);
            return 1;
        }

        buffer[bytesRead] = '\0';

        printf("Child process read first 10 characters: %s\n", buffer);

        close(fd);
    } else {
        wait(NULL); 
        printf("Parent process completes\n");
    }

    return 0;
}
