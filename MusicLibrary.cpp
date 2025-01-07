#include "MusicLibrary.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

std::string userPrefix = "user:";

void MusicLibrary::loadFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        throw std::runtime_error("Error: Could not open file " + fileName);
    }

    std::string line;
    std::string section;

    while (std::getline(file, line)) {
        if (line == "Media:") {
            section = "media";
            continue;
        } else if (line == "Utilizatori:") {
            section = "utilizatori";
            continue;
        } else if (line == "Playlist:") {
            section = "playlist";
            continue;
        }

        if (section == "media") {
            std::string type, title, details;
            double duration;

            type = line;
            std::getline(file, title);
            if (!(file >> duration)) {
                continue;
            }
            file.ignore();
            std::getline(file, details);

            if (type.find("Song") != std::string::npos) {
                mediaItems.push_back(std::make_unique<Song>(type, title, duration, details));
            } else if (type.find("Audiobook") != std::string::npos) {
                mediaItems.push_back(std::make_unique<Audiobook>(type, title, duration, details));
            } else if (type.find("Podcast") != std::string::npos) {
                mediaItems.push_back(std::make_unique<Podcast>(type, title, duration, details));
            }

        } else if (section == "utilizatori") {
            std::string username, email;

            username = line;
            if (!std::getline(file, email)) {
                continue;
            }

            users.emplace_back(username, email);
        } else if (section == "playlist") {
            std::string mediaTitle;
            Playlist* current_playlist = nullptr;

            do {
                if (line.rfind(userPrefix, 0) == 0) {
                    std::string username = line.substr(userPrefix.length());

                    auto userIt = std::find_if(users.begin(), users.end(), [&username](const User& u) {
                        return u.getUsername() == username;
                    });

                    if (userIt == users.end()) {
                        std::cerr << "user not found: " << username << std::endl;
                        exit(1);
                    }

                    if (current_playlist != nullptr) {
                        playlists.push_back(std::move(*current_playlist));
                    }

                    current_playlist = new Playlist(*userIt);

                    continue;
                }

                mediaTitle = line;

                auto mediaIt = std::find_if(mediaItems.begin(), mediaItems.end(),
                    [&mediaTitle](const std::unique_ptr<Media>& m) {
                        return m->getTitle() == mediaTitle;
                    });

                if (mediaIt == mediaItems.end()) {
                    std::cerr << "media not found: " << mediaTitle << std::endl;
                    exit(1);
                }

                current_playlist->addMedia(**mediaIt);
            } while (std::getline(file, line));

            playlists.push_back(std::move(*current_playlist));
        }
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


