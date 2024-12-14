#include <iostream>
#include <bitset>
#include <cstdlib>
#include <string>
#include <limits>

using namespace std;


// Constants
const int VIRTUAL_ADDRESS_BITS = 32;
const int PAGE_SIZE_BYTES = 2048; // 2 KB converted to bytes; 2 KB = 2048 bytes
const int PAGE_OFFSET_BITS = 11;   // log2(PAGE_SIZE): log2(2048) = 11 offset bits
const int PAGE_NUMBER_BITS = VIRTUAL_ADDRESS_BITS - PAGE_OFFSET_BITS;


// Function to validate if input is a valid non-negative integer
bool isValidNumber(const std::string &input) {
    if (input.empty()) return false;
    for (size_t i = 0; i < input.size(); ++i) {
        if (!isdigit(input[i])) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {

    // If the argument size is not 2
    if (argc != 2) {
        cout << "Usage: ./address virtual_address" << endl;
        return 1;
    }
    
    // Validate input
    string input = argv[1];
    if (!isValidNumber(input)) {
        cout << "Please provide a valid virtual address." << endl;
        return 1;
    }
    
    // Convert string to unsigned long and check for overflow
    unsigned long address;
    try {
        address = stoul(input);
        // Check for overflow
        if (address > UINT32_MAX) {
            cout << "Address exceeds 32-bit range." << endl;
            return 1;
        }
    } catch (const exception& e) {
        cout << "Please provide a valid virtual address." << endl;
        return 1;
    }
    
    // Create binary representation for the address
    bitset<VIRTUAL_ADDRESS_BITS> binary(address);
    
    // Calculate page number and offset
    unsigned int page_mask = (1u << PAGE_NUMBER_BITS) - 1;
    unsigned int offset_mask = (1u << PAGE_OFFSET_BITS) - 1;
    
    unsigned int page_number = (address >> PAGE_OFFSET_BITS) & page_mask;
    unsigned int page_offset = address & offset_mask;
    
    // Create binary representations for page number and offset
    bitset<PAGE_NUMBER_BITS> page_binary(page_number);
    bitset<PAGE_OFFSET_BITS> offset_binary(page_offset);
    
    // Output results
    cout << "The address " << address << " contains:" << endl;
    cout << "Binary: " << binary << endl;
    cout << "Number of bits for page number = " << PAGE_NUMBER_BITS << endl;
    cout << "Number of bits for page offset = " << PAGE_OFFSET_BITS << endl;
    cout << "Page number binary = " << page_binary << endl;
    cout << "Page offset binary = " << offset_binary << endl;
    cout << "Page number = " << page_number << endl;
    cout << "Page offset = " << page_offset << endl;
    
    return 0;
}
