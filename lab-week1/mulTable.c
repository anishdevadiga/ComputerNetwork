//Name: Shashank
//Regno: 230970004
//date: 25-07-2024

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int number;

    printf("Enter an integer: ");
    scanf("%d", &number);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        printf("Multiplication table for %d:\n", number);
        for (int i = 1; i <= 10; i++) {
            printf("%d x %d = %d\n", number, i, number * i);
        }
    } else {
        wait(NULL);
        printf("Parent process completes\n");
    }

    return 0;
}
