
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pp[2], pc[2];
    pid_t pid;
    int n, multiplier;

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
        int matrix[n][n];

        read(pp[0], matrix, sizeof(matrix));

        printf("Enter the multiplier: ");
        scanf("%d", &multiplier);

        int new_matrix[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                new_matrix[i][j] = matrix[i][j] * multiplier;
            }
        }

        write(pc[1], new_matrix, sizeof(new_matrix));
    } else {
        close(pp[0]);
        close(pc[1]);

        printf("Enter the size of the matrix (n x n): ");
        scanf("%d", &n);

        int matrix[n][n];
        printf("Enter the elements of the matrix:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }

        write(pp[1], &n, sizeof(n));
        write(pp[1], matrix, sizeof(matrix));

        wait(NULL);

        int new_matrix[n][n];
        read(pc[0], new_matrix, sizeof(new_matrix));

        printf("The new matrix is:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", new_matrix[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
