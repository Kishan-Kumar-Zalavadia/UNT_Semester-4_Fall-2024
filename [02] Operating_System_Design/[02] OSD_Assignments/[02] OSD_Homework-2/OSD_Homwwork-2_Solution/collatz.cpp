#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <cstring>
#include <vector>
#include <fcntl.h>

const char* SHARED_MEMORY = "/collatz_conjecture";
const size_t SHARED_MEMORY_SIZE = 4096;

struct Data {
    int length;
    int collatz_conjecture_sequence[4096];
};

void child(int num, Data* sharedData) {
    int index = 0;
    while (num!= 1) {
        sharedData->collatz_conjecture_sequence[index] = num;
        index++;
        if(num%2 == 0)
            num = num/2;
        else
          num = 3*num + 1;
    }
    sharedData->collatz_conjecture_sequence[index] = 1;
    sharedData->length = index + 1;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Syntax program num" << std::endl;
        return 1;
    }

    int num = std::atoi(argv[1]);

    if (num <= 0) {
        std::cout << "Please provide a positive integer." << std::endl;
        return 1;
    }

    int file_descriptor = shm_open(SHARED_MEMORY, O_CREAT | O_RDWR, 0666);
    if (file_descriptor == -1) {
        std::cerr << "Error creating shared memory: " << strerror(errno) << std::endl;
        return 1;
    }

    if (ftruncate(file_descriptor, SHARED_MEMORY_SIZE) == -1) {
        std::cerr << "Error creating shared memory: " << strerror(errno) << std::endl;
        shm_unlink(SHARED_MEMORY);
        return 1;
    }

    Data* sharedData = static_cast<Data*>(mmap(nullptr, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0));
    if (sharedData == MAP_FAILED) {
        std::cerr << "Error mapping shared memory: " << strerror(errno) << std::endl;
        shm_unlink(SHARED_MEMORY);
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Fork error: " << strerror(errno) << std::endl;
        munmap(sharedData, SHARED_MEMORY_SIZE);
        shm_unlink(SHARED_MEMORY);
        return 1;
    } 
    else if (pid == 0) {
      child(num, sharedData);
      exit(0);
    } 
    else {
      wait(nullptr);

      for (int i = 0; i < sharedData->length; i++) {
          std::cout << sharedData->collatz_conjecture_sequence[i];
          if (i < sharedData->length - 1) {
              std::cout << ", ";
          }
      }
      std::cout << std::endl;

      munmap(sharedData, SHARED_MEMORY_SIZE);
      shm_unlink(SHARED_MEMORY);
    }

    return 0;
}