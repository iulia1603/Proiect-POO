// main.cpp
#include "MusicLibrary.h"
#include <iostream>
#include <cstring>


int main(int argc, char* argv[]) {
    try {
        MusicLibrary library;
        std::string loadFromFile = "tastatura.txt";

        if (argc > 1) {
            if (strcmp(argv[1], "hibrid") == 0) {
                library.SetHibridLoading();
                if (argc > 2) {
                    loadFromFile = argv[2];
                }
            } else {
                loadFromFile = argv[1];
            }

            library.loadFromFile(loadFromFile);

            if (library.IsHibridLoading()) {
                library.displayMedia();
                library.displayUsers();
                std::cin >> library;
            }
        } else {
            std::cin >> library;
        }

        if (!library.IsHibridLoading()) {
            library.displayMedia();
            library.displayUsers();
        }

        std::cout << library << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
    }
    return 0;
}
