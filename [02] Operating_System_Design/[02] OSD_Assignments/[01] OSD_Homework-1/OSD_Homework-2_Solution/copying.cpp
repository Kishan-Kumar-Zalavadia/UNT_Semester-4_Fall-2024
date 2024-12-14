#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <chrono>
#include <sys/stat.h>

// Size of buffer
#define BUFFER_SIZE 1

// Function to copy file data
void readWriteFile(const char* sourceFile, const char* destinationFile) {
    char buffer[BUFFER_SIZE];

    // Source and Destination file descriptor
    int sourceFileDescriptor, destinationFileDescriptor;
    ssize_t bytesWriteCount, bytesReadCount;

    // Open the source file in read only mode
    sourceFileDescriptor = open(sourceFile, O_RDONLY);

    // Handle error condition while opening the source file
    if (sourceFileDescriptor == -1) {
        std::cerr << "Error occured while opening the file: " << sourceFile << std::endl;
        exit(1);
    }

    // Open the destination file - Create the file if it doesn't already exist
    destinationFileDescriptor = open(destinationFile, O_WRONLY | O_CREAT | O_APPEND);

    // Handle eroor condition while opening or creating the destination file
    if (destinationFileDescriptor == -1) {
        std::cerr << "Error occured while opening the file: " << destinationFile << std::endl;
        close(sourceFileDescriptor);
        exit(1);
    }

    // Read the data from source file descriptor and write to destination file descriptor
    while ((bytesReadCount = read(sourceFileDescriptor, buffer, BUFFER_SIZE)) > 0) {
        bytesWriteCount = write(destinationFileDescriptor, buffer, bytesReadCount);
        if (bytesReadCount != bytesWriteCount) {
            std::cerr << "Error occured while writing data in the file." << std::endl;
            // Close both the files after the read-write operation is completed
            close(sourceFileDescriptor);
            close(destinationFileDescriptor);
            exit(1);
        }
    }

    //  Handle error conditions
    if (bytesReadCount == -1) {
        std::cerr << "Error occoured while reading the data from source file" << std::endl;
        close(sourceFileDescriptor);
        close(destinationFileDescriptor);
        exit(1);
    }

    // Close both source and destination files
    close(sourceFileDescriptor);
    close(destinationFileDescriptor);
}

int main(int argc, char* argv[]) {

  // Handle error when proper arguments are not provided
  if (argc != 3) {
        std::cerr << "Pleaes provide source filename and destination file name as arguments" << std::endl;
        return 1;
    }

    // Record the start time
    auto startTime = std::chrono::high_resolution_clock::now();
    
    readWriteFile(argv[1], argv[2]);
    
    // Recod the end time
    auto endTime = std::chrono::high_resolution_clock::now();

    auto copyTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    // Print the duration to read data from source file to write the data to destination file
    std::cout << "Time taken to copy data from FileA to FileB: " << copyTime.count() / 1000000.0 << " seconds" << std::endl;

    return 0;
}


// Commands to create files with different sizes
/* 
  truncate -s 1K fileA_1KB
  truncate -s 2K fileA_2KB
  truncate -s 4K fileA_4KB
  truncate -s 8K fileA_8KB
  truncate -s 16K fileA_16KB
  truncate -s 32K fileA_32KB
  truncate -s 64K fileA_64KB
  truncate -s 128K fileA_128KB
  truncate -s 256K fileA_256KB
  truncate -s 512K fileA_512KB
  truncate -s 1M fileA_1MB
  truncate -s 2M fileA_2MB
  truncate -s 4M fileA_4MB
  truncate -s 8M fileA_8MB
  truncate -s 16M fileA_16MB
  truncate -s 32M fileA_32MB
  truncate -s 64M fileA_64MB
  truncate -s 128M fileA_128MB
*/

//  Commands to run the program
/*
  time ./copying fileA_1KB fileB_1KB
  time ./copying fileA_2KB fileB_2KB
  time ./copying fileA_4KB fileB_4KB
  time ./copying fileA_8KB fileB_8KB
  time ./copying fileA_16KB fileB_16KB
  time ./copying fileA_32KB fileB_32KB
  time ./copying fileA_64KB fileB_64KB
  time ./copying fileA_128KB fileB_128KB
  time ./copying fileA_256KB fileB_256KB
  time ./copying fileA_512KB fileB_512KB
  time ./copying fileA_1MB fileB_1MB
  time ./copying fileA_2MB fileB_2MB
  time ./copying fileA_4MB fileB_4MB
  time ./copying fileA_8MB fileB_8MB
  time ./copying fileA_16MB fileB_16MB
  time ./copying fileA_32MB fileB_32MB
  time ./copying fileA_64MB fileB_64MB
  time ./copying fileA_128MB fileB_128MB
*/
