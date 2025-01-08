// main.cpp
#include "MusicLibrary.h"
#include <iostream>
#include <cstring>


int main() {
    try {
        MusicLibrary library;

        try {
            library.loadFromFile("tastatura.txt");
        } catch (const FileOperationException& e) {
            std::cerr << "File error: " << e.what() << std::endl;
            return 1;
        }

        library.displayMedia();
        library.displayUsers();

        std::cout << std::endl;

        try {
            std::cin >> library;
        } catch (const UserNotFoundException& e) {
            std::cerr << "User error: " << e.what() << std::endl;
        } catch (const MediaNotFoundException& e) {
            std::cerr << "Media error: " << e.what() << std::endl;
        } catch (const InvalidDurationException& e) {
            std::cerr << "Duration error: " << e.what() << std::endl;
        }

        std::cout << library << std::endl;
    } catch (const MediaLibraryException& e) {
        std::cerr << "Library error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}