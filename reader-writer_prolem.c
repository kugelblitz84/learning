#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2
#define MAX_READS 5    // Maximum number of reads for each reader
#define MAX_WRITES 5   // Maximum number of writes for each writer

sem_t readLock; // Semaphore for reader access
sem_t writeLock; // Semaphore for writer access
int readCount = 0; // Count of active readers

void* reader(void* id) {
    int readerId = *(int*)id;

    for (int i = 0; i < MAX_READS; i++) {
        // Start reading
        sem_wait(&readLock); // Lock to update readCount
        readCount++;
        if (readCount == 1) {
            sem_wait(&writeLock); // First reader locks the writer
        }
        sem_post(&readLock); // Release the lock

        // Simulate reading
        printf("Reader %d is reading (%d).\n", readerId, i + 1);
        sleep(1); // Simulate time taken to read

        // Finished reading
        sem_wait(&readLock); // Lock to update readCount
        readCount--;
        if (readCount == 0) {
            sem_post(&writeLock); // Last reader unlocks the writer
        }
        sem_post(&readLock); // Release the lock

        sleep(rand() % 3); // Sleep for a random time before reading again
    }

    printf("Reader %d finished reading.\n", readerId);
    return NULL;
}

void* writer(void* id) {
    int writerId = *(int*)id;

    for (int i = 0; i < MAX_WRITES; i++) {
        // Start writing
        sem_wait(&writeLock); // Wait for exclusive access

        // Simulate writing
        printf("Writer %d is writing (%d).\n", writerId, i + 1);
        sleep(2); // Simulate time taken to write

        sem_post(&writeLock); // Release the lock

        sleep(rand() % 3); // Sleep for a random time before writing again
    }

    printf("Writer %d finished writing.\n", writerId);
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int readerIds[NUM_READERS], writerIds[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&readLock, 0, 1); // Binary semaphore for readers
    sem_init(&writeLock, 0, 1); // Binary semaphore for writers

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        readerIds[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerIds[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writerIds[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writerIds[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&readLock);
    sem_destroy(&writeLock);

    return 0;
}
