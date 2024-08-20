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
    char content[100];
    char buffer[100];
    ssize_t bytesRead;

    printf("Enter the filename: ");
    scanf("%s", filename);
    getchar();//Consume the newline character left by scanf
    printf("Enter the content to write to the file: ");
    fgets(content, sizeof(content), stdin);

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("Error opening file in parent process");
        return 1;
    }

    if (write(fd, content, sizeof(content)) == -1) {
        perror("Error writing to file in parent process");
        close(fd);
        return 1;
    }

    close(fd);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        fd = open(filename, O_RDONLY);
        if (fd == -1) {
            perror("Error opening file in child process");
            return 1;
        }

        bytesRead = read(fd, buffer, sizeof(buffer) - 1);
        if (bytesRead == -1) {
            perror("Error reading file in child process");
            close(fd);
            return 1;
        }

        buffer[bytesRead] = '\0';
        printf("Child process read from file: %s\n", buffer);

        close(fd);
    } else {
        wait(NULL);
        printf("Parent process completes\n");
    }

    return 0;
}