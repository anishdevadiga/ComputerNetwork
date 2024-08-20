
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pp[2], pc[2];
    pid_t pid;
    int n;
    pipe(pp);
    pipe(pc);

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        close(pp[1]);
        close(pc[0]);

        read(pp[0], &n, sizeof(n));

        int arr[n];
        read(pp[0], arr, sizeof(arr));
        close(pp[0]);

        int evenarr[n];
        int evencnt = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 == 0) {
                evenarr[evencnt++] = arr[i];
            }
        }

        write(pc[1], &evencnt, sizeof(evencnt));
        write(pc[1], evenarr, evencnt * sizeof(int));
        close(pc[1]);
    } else {
        close(pp[0]);
        close(pc[1]);

        printf("Enter the no. of elements: ");
        scanf("%d", &n);

        int arr[n];
        printf("Enter the elements: ");
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        write(pp[1], &n, sizeof(n));
        write(pp[1], arr, sizeof(arr));

        wait(NULL);

        int evncnt;
        read(pc[0], &evncnt, sizeof(evncnt));

        int even_arr[evncnt];
        read(pc[0], even_arr, evncnt * sizeof(int));
        close(pc[0]);

        printf("Even numbers: ");
        for (int i = 0; i < evncnt; i++) {
            printf("%d ", even_arr[i]);
        }
        printf("\n");
    }
    return 0;
}