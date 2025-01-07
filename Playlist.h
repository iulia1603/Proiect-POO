#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "User.h"
#include "Media.h"
#include <vector>
#include <memory>

class Playlist {
private:
    User user;
    std::vector<std::unique_ptr<Media>> mediaItems;

public:
    Playlist(const User& user) : user(user) {}

    void addMedia(const Media& media);
    double calculateTotalDuration() const;
    void display() const;

    friend std::ostream& operator<<(std::ostream& os, const Playlist& playlist);
};

#endif // PLAYLIST_H
