
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pp[2], pc[2];
    pid_t pid;
    char str[100], msg[20];
    pipe(pp);
    pipe(pc);

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        close(pp[1]);
        close(pc[0]);

        read(pp[0], str, sizeof(str));

        int len=0,flag=1;
        while(str[len]!='\0')
            len++;

        for (int i=0; i<len/2;i++) {
            if (str[i]!=str[len-1-i]) {
                flag=0;
                break;
            }
        }
        if(flag==1)
            write(pc[1],"PALINDROME", 11);
        else
            write(pc[1],"NOT PALINDROME", 15);
    } else {
        close(pp[0]);
        close(pc[1]);

        printf("Enter the string: ");
        scanf("%s",str);
        write(pp[1], str, sizeof(str));


        wait(NULL);

        read(pc[0], msg, sizeof(msg));

        printf("The string is: %s\n", msg);
    }

    return 0;
}