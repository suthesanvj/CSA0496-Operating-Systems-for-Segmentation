#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_CORES 4
#define NUM_THREADS 8

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct ThreadData {
    int threadID;
    int coreID;
    // Add any additional data needed for your specific application
};

void *threadFunction(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;

    // Simulate some processing
    printf("Thread %d on Core %d is running.\n", data->threadID, data->coreID);

    // Add your processing logic here

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    struct ThreadData threadData[NUM_THREADS];

    // Create threads and assign them to cores
    for (int i = 0; i < NUM_THREADS; ++i) {
        threadData[i].threadID = i;
        threadData[i].coreID = i % NUM_CORES; // Assign threads to cores in a round-robin fashion

        if (pthread_create(&threads[i], NULL, threadFunction, (void *)&threadData[i]) != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Error joining thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    printf("All threads have completed.\n");

    return 0;
}

