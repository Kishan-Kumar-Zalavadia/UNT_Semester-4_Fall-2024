#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

const int MAX_ITEMS = 20;
const int NUM_CONSUMERS = 7;

sem_t empty;
sem_t full; 
sem_t mutex;
int bucket = 0;

void* producer(void* arg) {
    while (true) {
       // Wait until the bucket is empty (signaled by consumer)
        sem_wait(&empty);
        sem_wait(&mutex);

        bucket = MAX_ITEMS;
        std::cout << "Producer produced " << MAX_ITEMS << " items in the bucket.\n";

        // Signal that the bucket is now full (signaled by consumer)
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }
    return nullptr;
}

void* consumer(void* arg) {
    int id = *((int*)arg);
    while (true) {
       // Wait until the bucket is full (signaled by producer)
        sem_wait(&full);
        sem_wait(&mutex);

        // Consume one item
        if (bucket > 0) {
            bucket--;
            std::cout << "Consumer " << id << " consumed an item. Remaining items: " << bucket << "\n";
        }

        // If bucket is empty after consumption, signal producer to produce more items
        if (bucket == 0) {
            sem_post(&empty);
        } else {
            sem_post(&full);
        }

        sem_post(&mutex);
        usleep(100000); 
    }
    return nullptr;
}

int main() {
    pthread_t prodThread;
    pthread_t consThreads[NUM_CONSUMERS];
    int consumerIDs[NUM_CONSUMERS];

    sem_init(&empty, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Producer thread
    pthread_create(&prodThread, nullptr, producer, nullptr);

    // Consumer threads
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumerIDs[i] = i + 1;
        pthread_create(&consThreads[i], nullptr, consumer, &consumerIDs[i]);
    }

    // Wait for threads to finish
    pthread_join(prodThread, nullptr);
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        pthread_join(consThreads[i], nullptr);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}


/*

  There may be scatterd print statements due to the parallel thread execution.
  This program will run continuously, use control+C to exit the program.
  
  Compile: g++ -pthread -o prodcons prodcons.cpp
  Run: ./prodcons
  
*/