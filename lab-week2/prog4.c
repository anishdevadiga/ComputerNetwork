
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pp[2], pc[2];
    pid_t pid;
    int regNo, mark1, mark2, mark3;

    pipe(pp);
    pipe(pc);
    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        close(pp[1]);
        close(pc[0]);

        read(pp[0], &regNo, sizeof(regNo));
        read(pp[0], &mark1, sizeof(mark1));
        read(pp[0], &mark2, sizeof(mark2));
        read(pp[0], &mark3, sizeof(mark3));

        float average = (mark1 + mark2 + mark3) / 3.0;
        char *grade;

        if (average >= 90) grade="A+";
        else if (average >= 80) grade= "A";
        else if (average >= 70) grade= "B";
        else if (average >= 60) grade= "C";
        else if (average >= 45) grade= "D";
        else if (average >= 30) grade= "E";
        else grade= "F";

        write(pc[1], grade,2);
    } else {
        close(pp[0]);
        close(pc[1]);

        printf("Enter Registration Number: ");
        scanf("%d", &regNo);
        printf("Enter Mark1: ");
        scanf("%d", &mark1);
        printf("Enter Mark2: ");
        scanf("%d", &mark2);
        printf("Enter Mark3: ");
        scanf("%d", &mark3);

        write(pp[1], &regNo, sizeof(regNo));
        write(pp[1], &mark1, sizeof(mark1));
        write(pp[1], &mark2, sizeof(mark2));
        write(pp[1], &mark3, sizeof(mark3));

        wait(NULL);

        char grade[2];
        read(pc[0], &grade, sizeof(grade));
        close(pc[0]);

        printf("The grade is: %s\n", grade);
    }

    return 0;
}