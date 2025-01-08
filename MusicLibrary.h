// MusicLibrary.h
#ifndef MUSIC_LIBRARY_H
#define MUSIC_LIBRARY_H

#include "Playlist.h"
#include "MediaFactory.h"
#include "Exceptions.h"
#include <fstream>
#include <algorithm>
#include <ctime> // Added this header

// Observer Pattern Implementation
class MediaPlaybackLogger : public MediaObserver {
public:
    void onMediaPlayed(const std::string& title) override {
        std::time_t now = std::time(nullptr);  // Changed to std::time
        std::cout << "Logged: " << title << " was played at " << now << std::endl;
    }
};

class MusicLibrary {
private:
    std::vector<std::unique_ptr<Media>> mediaItems;
    std::vector<User> users;
    std::vector<Playlist> playlists;
    MediaPlaybackLogger playbackLogger;

    void createMediaLists(std::istream& is);
    void loadMedia(std::ifstream& input);
    void loadUsers(std::ifstream& input);

public:
    MusicLibrary() {
        // Register media creators with the factory
        auto& factory = MediaFactory::getInstance();
        factory.registerCreator("Song", [](const std::string& title, double duration, const std::string& details) {
            return std::make_unique<Song>(title, "Song", duration, details);
        });
        factory.registerCreator("Audiobook", [](const std::string& title, double duration, const std::string& details) {
            return std::make_unique<Audiobook>(title, "Audiobook", duration, details);
        });
        factory.registerCreator("Podcast", [](const std::string& title, double duration, const std::string& details) {
            return std::make_unique<Podcast>(title, "Podcast", duration, details);
        });
    }

    void loadFromFile(const std::string& fileName);
    void displayMedia() const;
    void displayUsers() const;
    void displayPlaylists() const;

    // Member operator overload
    void operator+=(const Media& media) {
        mediaItems.push_back(media.clone());
    }

    friend std::ostream& operator<<(std::ostream& os, const MusicLibrary& library);
    friend std::istream& operator>>(std::istream& is, MusicLibrary& library);
};

#endif // MUSIC_LIBRARY_H