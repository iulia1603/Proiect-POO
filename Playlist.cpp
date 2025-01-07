// Playlist.cpp
#include "Playlist.h"
#include <iostream>

void Playlist::addMedia(const Media& media) {
    mediaItems.push_back(media.clone());
}

double Playlist::calculateTotalDuration() const {
    double total = 0;
    for (const auto& item : mediaItems) {
        total += item->getDuration();
    }
    return total;
}

void Playlist::display() const {
    std::cout << "\nPlaylist '" << "' by " << user.getUsername() << ":\n";
    for (const auto& item : mediaItems) {
        item->display();
    }
    std::cout << "Total Duration: " << calculateTotalDuration() << " minutes\n";
}

std::ostream& operator<<(std::ostream& os, const Playlist& playlist) {
    os << "\nPlaylist '" << "' by " << playlist.user.getUsername() << ":\n";
    for (const auto& item : playlist.mediaItems) {
        os << *item;
    }
    os << "Total Duration: " << playlist.calculateTotalDuration() << " minutes\n";
    return os;
}
