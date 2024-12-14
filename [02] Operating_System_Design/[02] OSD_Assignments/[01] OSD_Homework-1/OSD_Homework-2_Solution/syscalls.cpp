#include <stdio.h>
#include <iostream>
#include <string.h>
// Contains getpid(), getppid(), read(), write(), close()
#include <unistd.h>
// Contains open()
#include <fcntl.h>
// Contains chmod()
#include <sys/stat.h>

int main() {

    // (a) Get the process id and store it in process_id.
    pid_t process_id = getpid();  
    // Print the process Id.
    std::cout << "Process ID: " << process_id << std::endl << "\n";


    // (b) Get the parent process Id and store it in parent_process_id.
    pid_t parent_process_id = getppid();
    // Print the parent process Id.
    std::cout << "Parent Process ID: " << parent_process_id << std::endl << "\n";

    // (c) Open the file in read/write mode and create if it doesn't exist.
    const char* file_name = "input.txt";
    int file_descriptor = open(file_name, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    // Print error message if the open() returns is -1.
    if(file_descriptor == -1){
      std::cerr << "Error occurred while opening file." << std::endl << "\n";
      // (f) Close the file descriptor if any error occurred.
      close(file_descriptor);
      return 1;
    }
    std::cout << "File opened successfully." << std::endl << "\n";

    // (d) Read the data from file before writing the data in the file.
    // Initial the buffer with 0.
    char read_buffer_1[1024] = {0}; 
    ssize_t bytes_read_count_1 = read(file_descriptor, read_buffer_1, sizeof(read_buffer_1));
    // Print error message if the read() returns is -1.
    if (bytes_read_count_1 == -1) {
        std::cerr << "Error occurred while reading the file." << file_name << std::endl << "\n";
        // (f) Close the file descriptor if any error occurred.
        close(file_descriptor);
        return 1;
    }
    std::cout << "Data read from file." << std::endl;
    std::cout << "File data before writing: " << read_buffer_1 << std::endl;
    std::cout << "Data length before writing: " << bytes_read_count_1 << std::endl << "\n";

    // (e) Write to the file.
    const char* file_text = "Hello world! This is assignment 1 of operating system course.";
    ssize_t bytes_written_count = write(file_descriptor, file_text, strlen(file_text));
    // Print error message if the write() returns is -1.
    if(bytes_written_count == -1){
      std::cerr << "Error occurred while writing in the file." << std::endl << "\n";
      // (f) Close the file descriptor if any error occurred.
      close(file_descriptor);
      return 1;
    }
    std::cout << "File Descriptor for write(): " << file_descriptor << std::endl << "\n";
    std::cout << "Data written to file." << std::endl;
    // (f) Close the file descriptor after writing the data in the file.
    close(file_descriptor);

    // (d) Read the data from the file after writing the data in the file
    file_descriptor = open(file_name, O_RDONLY);
    // Print error message if the open() returns is -1.
    if (file_descriptor == -1) {
        std::cerr << "Error occured while opening the file to read."<< file_name << std::endl << "\n";
        // (f) Close the file descriptor if any error occurred.
        close(file_descriptor);
        return 1;
    }
    std::cout << "File Descriptor for read(): " << file_descriptor << std::endl << "\n";
    // Initial the buffer with 0.
    char read_buffer_2[1024]= {0};
    ssize_t bytes_read_count_2 = read(file_descriptor, read_buffer_2, sizeof(read_buffer_2));
    // Print error message if the read() returns is -1.
    if(bytes_read_count_2 == -1) {
      std::cerr << "Error occured while reading the file." << file_name << std::endl << "\n";
      // (f) Close the file descriptor if any error occurred.
      close(file_descriptor);
      return 1;
    }
    std::cout << "File data after writing: " << read_buffer_2 << std::endl;
    std::cout << "File data length: " << bytes_read_count_2 << std::endl << "\n";
    // (f) Close the file descriptor after reading the data from the file.
    close(file_descriptor);

    // (g)
    if (chmod("input.txt", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1) {
        std::cerr << "Error occured while changing file permission for " << file_name << std::endl << "\n";
        return 1;
    }

    std::cout << "File permissions changed successfully for " << file_name << std::endl << "\n";


    return 0;  
}