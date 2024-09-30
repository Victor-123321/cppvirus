#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;

const int BLOCK_SIZE = 4096; // Process 4KB chunks

// Simple XOR encryption/decryption
void processFile(const fs::path& filePath, int opc, char key) {
    std::cout << "Processing file: " << filePath << std::endl;

    std::fstream file(filePath, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    std::vector<char> buffer(BLOCK_SIZE); // Buffer to store file data

    while (file.read(buffer.data(), BLOCK_SIZE) || file.gcount() > 0) {
        std::streamsize bytesRead = file.gcount();
        // XOR each byte in the block with the key
        for (std::streamsize i = 0; i < bytesRead; ++i) {
            buffer[i] ^= key; // XOR operation
        }
        file.seekp(-bytesRead, std::ios::cur); // Move back to the start of the block
        file.write(buffer.data(), bytesRead);  // Write the modified block
    }

    file.close();
}

void processDirectory(const fs::path& directoryPath, int opc, char key) {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (fs::is_directory(entry)) {
            processDirectory(entry.path(), opc, key); // Recursive call for subdirectory
        }
        else if (fs::is_regular_file(entry)) {
            processFile(entry.path(), opc, key); // Process the file
        }
    }
}

int main() {
    system("Color 0A"); // Stylish matrix color

    fs::path rootPath = "C:\\Users\\joldo\\Desktop\\virus";

    if (!fs::exists(rootPath) || !fs::is_directory(rootPath)) {
        std::cerr << "Invalid directory: " << rootPath << std::endl;
        return 1;
    }

    int option;
    char key; // Key for XOR encryption
    std::cout << "What we doing boss?\n1) Encrypt\n2) Decrypt\n3) Close\n\nChoose: ";
    std::cin >> option;

    if (option == 1 || option == 2) {
        std::cout << "Enter key (single character): ";
        std::cin >> key;
        processDirectory(rootPath, option, key);
    }

    return 0;
}

