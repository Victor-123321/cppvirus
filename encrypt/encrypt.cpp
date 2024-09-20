#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
void processFile(const fs::path& filePath, int opc) {
    std::cout << "Processing file: " << filePath << std::endl;
    std::fstream file(filePath, std::ios::in | std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
    }

    char byte;
    int x = 0;
    if (opc == 1) {
        while (file.read(&byte, 1)) {
            std::cout << &byte; //show the byte's content, remove the ampersand to show the literal byte
            byte++; // Add 1 to the byte
            file.seekp(-1, std::ios::cur); // Move the pointer back one position
            file.write(&byte, 1); // Write the modified byte back to the file
            file.seekp(1, std::ios::cur); //Advance position
        }
    }
    else {
        while (file.read(&byte, 1)) {
            std::cout << &byte; //show the byte's content, remove the ampersand to show the literal byte
            byte--; // Remove 1 to the byte
            file.seekp(-1, std::ios::cur); // Move the pointer back one position
            file.write(&byte, 1); // Write the modified byte back to the file
            file.seekp(1, std::ios::cur); //Advance position
        }
    }
       file.close();
}
void processDirectory(const fs::path& directoryPath, int opc) {
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        //Detects if the file is a folder, if so, it enters it
        if (fs::is_directory(entry)) {
            // Recursive call to process subdirectory
            processDirectory(entry.path(), opc);
        }
        else if (fs::is_regular_file(entry)) {
            // Process regular (non-folder) file
            processFile(entry.path(), opc);
        }
    }

//Trolling complete

std::cout << "\n\n\n\n\n\n------------------------------------------------------------\n\n\n\n\n\n";
std::cout << "Process Complete";
std::cout << "\n\n\n\n\n\n------------------------------------------------------------\n\n\n\n\n\n";
 
}

int main() {
    system("Color 0A"); //some cool matrix color for extra style points

    // Folder that's going to get bombed
    fs::path rootPath = "C:\\Users\\joldo\\Desktop\\Testeos"; 

    // Confirm that the folder, in fact, is an actual folder
    if (!fs::exists(rootPath) || !fs::is_directory(rootPath)) { 
        std::cerr << "Invalid directory: " << rootPath << std::endl; 
        return 1;
    }


    int option;
    std::cout << "What we doing boss?\n1) Encrypt\n2) Decryptshit\n3) Close\n\nChoose: ";
    std::cin >> option;
    if(option == 1 || option == 2)
    processDirectory(rootPath, option);

    return 0;
}
