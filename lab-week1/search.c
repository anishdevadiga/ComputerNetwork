//Name: Shashank
//Regno: 230970004
//date: 25-07-2024

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int n, key;

    printf("Enter the no. of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the element to search for: ");
    scanf("%d", &key);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        int loc=-1;
        for (int i = 0; i < n; i++) {
            if (arr[i] == key){
                loc=i;break;
            }
        }
        if (loc == -1) {
            printf("Element %d not found.\n", key);
        } else {
            printf("Element %d found at index %d.\n", key, loc);
        }
    } else {
        wait(NULL);
        printf("Parent process completes\n");
    }

    return 0;
}
