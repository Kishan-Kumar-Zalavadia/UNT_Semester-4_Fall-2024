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
    long long int allPoints = *((long long int*)arg);

    for(long long int i = 0; i < allPoints; ++i) {
        double x = 2.0 * ((double)rand() / RAND_MAX) - 1.0;
        double y = 2.0 * ((double)rand() / RAND_MAX) - 1.0;

        if (x*x + y*y <= 1.0)
            pointsInsideCircleLocal++;
    }

    pthread_mutex_lock(&mutex);
    pointsInsideCircleGlobal += pointsInsideCircleLocal;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Syntax program num" << std::endl;
        return 1;
    }

    totalPoints = std::atoll(argv[1]);

    if (totalPoints <= 0) {
        std::cout << "Please provide a positive number of points." << std::endl;
        return 1;
    }

    srand(time(NULL));

    pthread_t thread;
    int rc = pthread_create(&thread, NULL, generate_points, (void*)&totalPoints);
    if (rc) {
        std::cout << "Error creating thread; return code from pthread_create() is " << rc << std::endl;
        return 1;
    }

    pthread_join(thread, NULL);

    double pi_value = 4.0 * pointsInsideCircleGlobal / totalPoints;

    std::cout << "Total count of points inside the circle = " << pointsInsideCircleGlobal << std::endl;
    std::cout << "Value of PI using Monte Carlo technique with " << totalPoints << " random points = " << pi_value << std::endl;

    return 0;
}