#include "MusicLibrary.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

std::string userPrefix = "user:";

std::istream& operator>>(std::istream& is, MusicLibrary& library) {
    std::cout << "Create media lists" << std::endl;

    library.createMediaLists(is);
    return is;
}

void MusicLibrary::createMediaLists(std::istream& is) {
    std::string username, mediaTitle;

    while (1) {
        std::cout << "username for media list: (media lists added: " << playlists.size() << ")" << std::endl;
        is >> username;

        if (username.find(".next") != std::string::npos) {
            return;
        }

        auto userIt = std::find_if(users.begin(), users.end(), [&username](const User& u) {
            return u.getUsername() == username;
        });

        if (userIt == users.end()) {
            throw UserNotFoundException(username);
        }

        Playlist playlist(*userIt);
        while(1) {
            std::cout << "media title:" << std::endl;
            is >> mediaTitle;

            if (mediaTitle.find(".next") != std::string::npos) {
                break;
            }

            auto mediaIt = std::find_if(mediaItems.begin(), mediaItems.end(), [&mediaTitle](const std::unique_ptr<Media>& m) {
                return m->getTitle() == mediaTitle;
            });

            if (mediaIt == mediaItems.end()) {
                throw MediaNotFoundException(mediaTitle);
            }

            playlist.addMedia(**mediaIt);

            std::cout << "write .next to finish adding media" << std::endl;
        }
        playlists.push_back(std::move(playlist));

        std::cout << "write .next to finish adding playlists" << std::endl;
    }
}


void MusicLibrary::loadFromFile(const std::string& fileName) {
    std::ifstream input(fileName);
    if (!input) {
        throw FileOperationException("Could not open file: " + fileName);
    }

    std::string line;
    try {
        while (std::getline(input, line)) {
            if (line == "Media:") {
                loadMedia(input);
            } else if (line == "Users:") {
                loadUsers(input);
            }
        }
    } catch (const MediaLibraryException& e) {
        throw;  // Retransmitem excepția
    } catch (const std::exception& e) {
        throw FileOperationException("Error reading file: " + std::string(e.what()));
    }
}



void MusicLibrary::loadMedia(std::ifstream& input) {
    std::string line;

    while (std::getline(input, line)) {
        if (line.empty()) {
            break;
        }

        std::string type, title, details;
        double duration;

        title = line;

        if (!(input >> duration)) {
            std::cout << "can't parse duration (must by double)" << std::endl;
            exit(1);
        }
        input.ignore();

        std::getline(input, type);
        std::getline(input, details);

        if (type == "Song") {
            mediaItems.push_back(std::make_unique<Song>(title, type, duration, details));
        } else if (type == "Audiobook") {
            mediaItems.push_back(std::make_unique<Audiobook>(title, type, duration, details));
        } else if (type == "Podcast") {
            mediaItems.push_back(std::make_unique<Podcast>(title, type, duration, details));
        } else {
            std::string customType;
            std::getline(input, customType);

            if (customType.compare("Price") == 0) {
                int intPrice;
                input >> intPrice;

                mediaItems.push_back(std::make_unique<TemplateMedia<int>>(title, type, duration, details, customType, intPrice));
            } else {
                std::string customValue;
                std::getline(input, customValue);
                mediaItems.push_back(std::make_unique<TemplateMedia<std::string>>(title, type, duration, details, customType, customValue));
            }
        }
    }
}

void MusicLibrary::loadUsers(std::ifstream& input) {
    std::string line;

    while (std::getline(input, line)) {
        if (line.empty()) {
            break;
        }

        std::string username, email;

        username = line;
        std::getline(input, email);

        users.emplace_back(username, email);
    }
}

void MusicLibrary::displayMedia() const {
    std::cout << " ========================= Media Library ========================== " << std::endl;
    for (const auto& media : mediaItems) {
        media->display();
    }
}

void MusicLibrary::displayUsers() const {
    std::cout << " ========================= Users =========================== " << std::endl;
    for (const auto& user : users) {
        user.display();
    }
}

void MusicLibrary::displayPlaylists() const {
    std::cout << " ========================= Playlists =========================== " << std::endl;
    for (const auto& playlist : playlists) {
        playlist.display();
    }
}

std::ostream& operator<<(std::ostream& os, const MusicLibrary& library) {
    os << " ========================= Playlists =========================== " << std::endl;
    for (const auto& playlist : library.playlists) {
        os << playlist;
    }
    return os;
}