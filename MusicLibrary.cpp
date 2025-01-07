#include "MusicLibrary.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

std::string userPrefix = "user:";

std::istream& operator>>(std::istream& is, MusicLibrary& library) {
    std::cout << "Input data" << std::endl;

    if (!library.hibridLoading) {
        library.loadMedia(is);
        library.loadUsers(is);
    }

    library.loadPlaylists(is);
    return is;
}

void MusicLibrary::loadPlaylists(std::istream& is) {
    std::string username, mediaTitle;

    while (1) {
        std::cout << "username for playlist: (playlists added: " << playlists.size() << ")" << std::endl;
        is >> username;

        if (username.find(".next") != std::string::npos) {
            return;
        }

        auto userIt = std::find_if(users.begin(), users.end(), [&username](const User& u) {
            return u.getUsername() == username;
        });

        if (userIt == users.end()) {
            std::cout << "user not found" << std::endl;
            continue;
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
                std::cerr << "media not found: " << mediaTitle << std::endl;
                continue;
            }

            playlist.addMedia(**mediaIt);

            std::cout << "write .next to finish adding media" << std::endl;
        }
        playlists.push_back(std::move(playlist));

        std::cout << "write .next to finish adding playlists" << std::endl;
    }
}

void MusicLibrary::loadUsers(std::istream& is) {
    std::string username, email;

    while (1) {
        std::cout << "username: (users added: " << users.size() << ")" << std::endl;
        is >> username;

        if (username.find(".next") != std::string::npos) {
            return;
        }

        std::cout << "email:" << std::endl;
        is >> email;

        users.emplace_back(username, email);

        std::cout << "write .next to proceed to playlists" << std::endl;
    }
}

void MusicLibrary::loadMedia(std::istream& is) {
    std::string type, title, details, tipSpec;
    double duration;

    while (1) {
        std::cout << "Media type (song/audiobook/podcast) - added so far: " << mediaItems.size() << std::endl;
        is >> type;

        if (type.find(".next") != std::string::npos) {
            return;
        }

        std::cout << "Title: " << std::endl;
        is >> title;

        std::cout << "Duration (minutes):" << std::endl;
        is >> duration;

        std::cout << "Details (artist/author/host):" << std::endl;
        is >> details;

        if (type == "song") {
            std::cout << "Artist:" << std::endl;
            is >> details;
            mediaItems.push_back(std::make_unique<Song>(title, type, duration, details));
        } else if (type == "audiobook") {
            std::cout << "Narator:" << std::endl;
            is >> details;
            mediaItems.push_back(std::make_unique<Audiobook>(title, type, duration, details));
        } else if (type == "podcast") {
            std::cout << "Host:" << std::endl;
            is >> details;
            mediaItems.push_back(std::make_unique<Podcast>(title, type, duration, details));
        }

        std::cout << "write .next to proceed to users" << std::endl;
    }
}

void MusicLibrary::loadFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        throw std::runtime_error("Error: Could not open file " + fileName);
    }
    loadData(file);
}

void MusicLibrary::loadData(std::ifstream& input) {
    std::string line;
    std::string section;

    while (std::getline(input, line)) {
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
            std::getline(input, title);
            if (!(input >> duration)) {
                continue;
            }
            input.ignore();
            std::getline(input, details);

            if (type == "Song") {
                mediaItems.push_back(std::make_unique<Song>(title, type, duration, details));
            } else if (type == "Audiobook") {
                mediaItems.push_back(std::make_unique<Audiobook>(title, type, duration, details));
            } else if (type == "Podcast") {
                mediaItems.push_back(std::make_unique<Podcast>(title, type, duration, details));
            }

        } else if (section == "utilizatori") {
            std::string username, email;

            username = line;
            if (!std::getline(input, email)) {
                continue;
            }

            users.emplace_back(username, email);
        } else if (section == "playlist") {
            if (hibridLoading) {
                continue;
            }

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
            } while (std::getline(input, line));

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

std::ostream& operator<<(std::ostream& os, const MusicLibrary& library) {
    os << " ========================= Playlists =========================== " << std::endl;
    for (const auto& playlist : library.playlists) {
        os << playlist;
    }
    return os;
}