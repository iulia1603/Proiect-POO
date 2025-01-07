#include "MusicLibrary.h"
#include <iostream>

int main() {
    try {
        MusicLibrary library;
        library.loadFromFile("tastatura.txt");

        library.displayMedia();
        library.displayUsers();
        library.displayPlaylists();
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
    }

    return 0;
}