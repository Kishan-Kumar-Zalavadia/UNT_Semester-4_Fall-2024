#include <iostream>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutexA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexB = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexC = PTHREAD_MUTEX_INITIALIZER;

// Thread 1 tries to acquire mutexA then mutexB
void* thread1_function(void*) {
    std::cout << "Thread 1: Trying to lock mutexA \n";
    pthread_mutex_lock(&mutexA);
    std::cout << "Thread 1: Acquired mutexA \n";
    
    sleep(1);
    
    std::cout << "Thread 1: Trying to lock mutexB \n";
    pthread_mutex_lock(&mutexB);
    std::cout << "Thread 1: Acquired mutexB \n";
    
    pthread_mutex_unlock(&mutexB);
    pthread_mutex_unlock(&mutexA);
    
    return NULL;
}

// Thread 2 tries to acquire mutexB then mutexC
void* thread2_function(void*) {
    std::cout << "Thread 2: Trying to lock mutexB \n";
    pthread_mutex_lock(&mutexB);
    std::cout << "Thread 2: Acquired mutexB \n";
    
    sleep(1);
    
    std::cout << "Thread 2: Trying to lock mutexC \n";
    pthread_mutex_lock(&mutexC); 
    std::cout << "Thread 2: Acquired mutexC \n";
    
    pthread_mutex_unlock(&mutexC);
    pthread_mutex_unlock(&mutexB);
    
    return NULL;
}

// Thread 1 tries to acquire mutexC then mutexA
void* thread3_function(void*) {
    std::cout << "Thread 3: Trying to lock mutexC \n";
    pthread_mutex_lock(&mutexC);
    std::cout << "Thread 3: Acquired mutexC \n";
    
    sleep(1);
    
    std::cout << "Thread 3: Trying to lock mutexA \n";
    pthread_mutex_lock(&mutexA); 
    std::cout << "Thread 3: Acquired mutexA \n";
    
    pthread_mutex_unlock(&mutexA);
    pthread_mutex_unlock(&mutexC);
    
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;
    
    std::cout << "Creating threads... \n";
    
    // Create threads and join them
    if (pthread_create(&thread1, NULL, thread1_function, NULL) != 0) {
        std::cerr << "Failed to create thread 1 \n";
        return 1;
    }
    std::cout << "Thread 1 id: " << thread1 << " created.\n";
    if (pthread_create(&thread2, NULL, thread2_function, NULL) != 0) {
        std::cerr << "Failed to create thread 2 \n";
        return 1;
    }
    std::cout << "Thread 2 id: " << thread2 << " created.\n";
    if (pthread_create(&thread3, NULL, thread3_function, NULL) != 0) {
        std::cerr << "Failed to create thread 3 \n";
        return 1;
    }
    std::cout << "Thread 3 id: " << thread3 << " created.\n";

    std::cout << "Waiting for threads to finish... \n";
    
    // Joining threads to prevent program termination before deadlock occurs
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    
    std::cout << "Threads finished \n";
    
    // Destroy mutexes
    pthread_mutex_destroy(&mutexA);
    pthread_mutex_destroy(&mutexB);
    pthread_mutex_destroy(&mutexC);
    
    return 0;
}

/*
  Compile: g++ deadlock.cpp -o deadlock -pthread
  Run: ./deadlock
*/