#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

void display(int p, int *process, int allocation[], int b, int *block) {
    printf("Process \t Block   \t Internal fragmentation\n");
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
void bestfit(int p, int *process, int b, int *block) {
    int allocation[p];
    int blockallocated[b];

    // Initialize blockallocated array to represent unallocated blocks
    for (int i = 0; i < b; i++) {
        blockallocated[i] = 0;
    }

    // Initialize allocation array to represent unallocated processes
    for (int i = 0; i < p; i++) {
        allocation[i] = -1;
    }

    // Iterate through each process to find the best fit block
    for (int i = 0; i < p; i++) {
        int bestBlock = -1; // Index of the best fit block
        int minBlockSize = INT_MAX; // Minimum size of the best fit block

        // Iterate through each block to find the best fit for the current process
        for (int j = 0; j < b; j++) {
            if (block[j] >= process[i] && blockallocated[j] == 0) {
                if (block[j] < minBlockSize) {
                    minBlockSize = block[j];
                    bestBlock = j;
                }
            }
        }

        // Allocate the best fit block to the current process
        if (bestBlock != -1) {
            allocation[i] = bestBlock;
            blockallocated[bestBlock] = 1;
        }
    }

    // Display the allocation result
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

    bestfit(p, process, b, block);

    free(block);   // Free dynamically allocated memory
    free(process); // Free dynamically allocated memory

    return 0;
}
