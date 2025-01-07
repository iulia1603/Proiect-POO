#ifndef MUSIC_LIBRARY_H
#define MUSIC_LIBRARY_H

#include "Playlist.h"
#include <fstream>
#include <algorithm>
#include <exception>
#include <memory>
#include <vector>
#include <string>

class MusicLibrary {
private:
    std::vector<std::unique_ptr<Media>> mediaItems;
    std::vector<User> users;
    std::vector<Playlist> playlists;

public:
    MusicLibrary() = default;
    MusicLibrary(const MusicLibrary& other);
    MusicLibrary& operator=(const MusicLibrary& other);

    void loadFromFile(const std::string& fileName);
    void displayMedia() const;
    void displayUsers() const;
    void displayPlaylists() const;
};

#endif // MUSIC_LIBRARY_H
