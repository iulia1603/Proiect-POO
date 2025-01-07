#include "Playlist.h"
#include <iostream>

void Playlist::addMedia(const Media& media) {
    mediaItems.push_back(media.clone());
}

double Playlist::calculateTotalDuration() const {
    double total = 0;
    for (const auto& media : mediaItems) {
        total += media->getDuration();
    }
    return total;
}

void Playlist::display() const {
    std::cout << "\nPlaylist for " << user.getUsername() << ":\n";

    for (const auto& media : mediaItems) {
        media->display();
    }
    std::cout << "Total Duration: " << calculateTotalDuration() << " minutes\n";
}

