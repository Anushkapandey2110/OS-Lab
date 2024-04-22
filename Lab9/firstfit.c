#include<stdio.h>
#include<stdlib.h>

void display(int p, int *process, int allocation[], int b, int *block) {
    printf("Process \t Block   \t Block Size\n");
    for (int i = 0; i < p; i++) {
        printf("%d \t\t ", process[i]);
        if (allocation[i] != -1) {
            printf("%d \t\t ", allocation[i]+1); // Print allocated block number
        } else {
            printf("Not allocated");
        }
        printf("%d\n",(block[allocation[i]]-process[i]));
    }
}


void firstfit(int p, int *process, int b, int *block) {
    int blockallocated[b];
    int allocation[p];
    for (int i = 0; i < b; i++) {
        blockallocated[i] = 0;
    }
    for (int i = 0; i < p; i++) {
        allocation[i] = 0;
    }
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < b; j++) {
            if (blockallocated[j] == 0 && process[i] <= block[j]) {
                allocation[i] = j;
                blockallocated[j] = 1;
                break; // No need to check other blocks once allocated
            }
        }
    }
    display(p, process, allocation, b, block);
}

int main() {
    int b, p;
    printf("Enter the number of blocks: ");
    scanf("%d", &b);
    printf("Enter the number of processes: ");
    scanf("%d", &p);

    int *block = (int *)malloc(sizeof(int) * b);
    int *process = (int *)malloc(sizeof(int) * p);

    if (block == NULL || process == NULL) {
        printf("Memory allocation failed\n");
        return 1; // Exit with failure status
    }

    printf("Enter the process sizes: ");
    for (int i = 0; i < p; i++) {
        scanf("%d", &process[i]);
    }

    printf("Enter the block sizes: ");
    for (int i = 0; i < b; i++) {
        scanf("%d", &block[i]);
    }

    firstfit(p, process, b, block);

    free(block);   // Free dynamically allocated memory
    free(process); // Free dynamically allocated memory

    return 0;
}
