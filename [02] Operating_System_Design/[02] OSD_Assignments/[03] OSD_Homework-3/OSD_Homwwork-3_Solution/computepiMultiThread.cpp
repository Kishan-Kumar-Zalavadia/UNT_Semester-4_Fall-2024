#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <pthread.h>

long long int totalPoints = 0;
long long int pointsInsideCircleGlobal = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* generate_points(void* arg) {
    long long int pointsInsideCircleLocal = 0;
    long long int pointsPerThread = *((long long int*)arg);

    for (long long int i = 0; i < pointsPerThread; ++i) {
        double x = 2.0 * ((double)rand() / RAND_MAX) - 1.0;
        double y = 2.0 * ((double)rand() / RAND_MAX) - 1.0;

        // If point is inside the circle
        if (x * x + y * y <= 1.0) {
            pointsInsideCircleLocal++;
        }
    }

    // Lock before updating the global count and unlock after updating
    pthread_mutex_lock(&mutex);
    pointsInsideCircleGlobal += pointsInsideCircleLocal;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Syntax: program num_points" << std::endl;
        return 1;
    }

    totalPoints = std::atoll(argv[1]);

    if (totalPoints <= 0) {
        std::cout << "Please provide a positive number of points." << std::endl;
        return 1;
    }

    const int numThreads = 15;
    pthread_t threads[numThreads];
    long long int pointsPerThread = totalPoints / numThreads;

    srand(time(NULL));

    // Create and start 15 threads
    for (int i = 0; i < numThreads; ++i) {
        int rc = pthread_create(&threads[i], NULL, generate_points, (void*)&pointsPerThread);
        if (rc) {
            std::cout << "Error creating thread " << i << "; return code from pthread_create() is " << rc << std::endl;
            return 1;
        } else {
            std::cout << "Generating " << totalPoints << " number of random numbers in thread id = " << threads[i] << std::endl;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], NULL);
    }

    double pi_value = 4.0 * pointsInsideCircleGlobal / totalPoints;

    std::cout << "Total count of points inside the circle = " << pointsInsideCircleGlobal << std::endl;
    std::cout << "In main thread, value of PI using Monte Carlo technique with " << totalPoints << " random points = " << pi_value << std::endl;


    pthread_mutex_destroy(&mutex);

    return 0;
}


/*
  Compile:  g++ computepiMultiThread.cpp -o computepiMultiThread -pthread
  Run: ./computepiMultiThread 99999
*/