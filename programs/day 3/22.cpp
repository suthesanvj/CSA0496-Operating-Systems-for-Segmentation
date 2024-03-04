#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 50

// Structure to represent a memory block
struct MemoryBlock {
    int size;
    int allocated;  // 0 if block is free, 1 if allocated
};

// Function to initialize memory blocks
void initializeMemory(struct MemoryBlock* memory, int numBlocks) {
    for (int i = 0; i < numBlocks; ++i) {
        memory[i].size = 0;
        memory[i].allocated = 0;
    }
}

// Function to display the memory blocks
void displayMemory(struct MemoryBlock* memory, int numBlocks) {
    printf("Memory Blocks:\n");
    for (int i = 0; i < numBlocks; ++i) {
        printf("Block %d: Size = %d, Allocated = %s\n", i + 1, memory[i].size,
               memory[i].allocated ? "Yes" : "No");
    }
    printf("\n");
}

// Function to allocate memory using best fit algorithm
void bestFit(struct MemoryBlock* memory, int numBlocks, int requestSize) {
    int bestFitIndex = -1;
    int bestFitSize = MAX_BLOCKS + 1;

    // Find the smallest available block that fits the request
    for (int i = 0; i < numBlocks; ++i) {
        if (!memory[i].allocated && memory[i].size >= requestSize && memory[i].size < bestFitSize) {
            bestFitSize = memory[i].size;
            bestFitIndex = i;
        }
    }

    // Allocate memory if a suitable block is found
    if (bestFitIndex != -1) {
        memory[bestFitIndex].allocated = 1;
        printf("Allocated %d units of memory from Block %d using Best Fit.\n\n",
               requestSize, bestFitIndex + 1);
    } else {
        printf("Memory allocation failed for request of size %d using Best Fit.\n\n",
               requestSize);
    }
}

int main() {
    int numBlocks;
    
    printf("Enter the number of memory blocks: ");
    scanf("%d", &numBlocks);

    if (numBlocks <= 0 || numBlocks > MAX_BLOCKS) {
        printf("Invalid number of memory blocks. Exiting...\n");
        return 1;
    }

    struct MemoryBlock memory[MAX_BLOCKS];

    initializeMemory(memory, numBlocks);

    int choice;
    do {
        printf("1. Display Memory\n");
        printf("2. Allocate Memory (Best Fit)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayMemory(memory, numBlocks);
                break;
            case 2:
                int requestSize;
                printf("Enter the size of memory to allocate: ");
                scanf("%d", &requestSize);
                bestFit(memory, numBlocks, requestSize);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 3);

    return 0;
}

