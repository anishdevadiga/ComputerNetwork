//Name: Shashank
//Regno: 230970004
//date: 25-07-2024

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <num1> <operator> <num2>\n", argv[0]);
        return 1;
    }

    double num1 = atof(argv[1]);
    double num2 = atof(argv[3]);
    char operator = argv[2][0];
    double result;

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        switch (operator) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':   //* is wildard in cmd give it within single quote '*'
                result = num1 * num2;
                break;
            case '/':
                if (num2 == 0) {
                    fprintf(stderr, "Error: Division by zero\n");
                    return 1;
                }
                result = num1 / num2;
                break;
            default:
                fprintf(stderr, "Error: Invalid operator. Use +, -, *, or /\n");
                return 1;
        }
        printf("Result: %f %c %f = %f\n", num1, operator, num2, result);
    } else {
        wait(NULL);
        printf("Parent process completes\n");
    }

    return 0;
}