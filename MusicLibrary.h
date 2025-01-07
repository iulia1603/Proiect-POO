// MusicLibrary.h
#ifndef MUSIC_LIBRARY_H
#define MUSIC_LIBRARY_H

#include "Playlist.h"
#include <fstream>
#include <algorithm>
#include <exception>

class MusicLibrary {
private:
    std::vector<std::unique_ptr<Media>> mediaItems;
    std::vector<User> users;
    std::vector<Playlist> playlists;
    bool hibridLoading = false;

    void loadData(std::ifstream& input);
    void loadMedia(std::istream& is);
    void loadUsers(std::istream& is);
    void loadPlaylists(std::istream& is);

public:
    void SetHibridLoading() { hibridLoading = true; }
    bool IsHibridLoading() { return hibridLoading; }

    void loadFromFile(const std::string& fileName);
    void displayMedia() const;
    void displayUsers() const;
    void displayPlaylists() const;

    friend std::ostream& operator<<(std::ostream& os, const MusicLibrary& library);
    friend std::istream& operator>>(std::istream& is, MusicLibrary& library);
};

#endif // MUSIC_LIBRARY_H
