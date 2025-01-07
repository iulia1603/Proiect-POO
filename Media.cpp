// Media.cpp
#include "Media.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Media& media) {
    media.print(os);
    return os;
}

void Song::display() const {
    print(std::cout);
}

std::unique_ptr<Media> Song::clone() const {
    return std::make_unique<Song>(*this);
}

void Audiobook::display() const {
    print(std::cout);
}

std::unique_ptr<Media> Audiobook::clone() const {
    return std::make_unique<Audiobook>(*this);
}

void Podcast::display() const {
    print(std::cout);
}

std::unique_ptr<Media> Podcast::clone() const {
    return std::make_unique<Podcast>(*this);
}
