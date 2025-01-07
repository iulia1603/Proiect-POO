#include "Media.h"
#include <iostream>
#include<cmath>

void Song::display() const {
    std::cout << type << ": " << title << " | Duration: " << duration
              << " min | Artist: " << artist << "\n";
}

std::unique_ptr<Media> Song::clone() const {
    return std::make_unique<Song>(*this);
}

void Audiobook::display() const {
    std::cout << type << ": " << title << " | Duration: " << duration
              << " min | Author: " << author << "\n";
}

std::unique_ptr<Media> Audiobook::clone() const {
    return std::make_unique<Audiobook>(*this);
}

void Podcast::display() const {
    std::cout << type << ": " << title << " | Duration: " << duration
              << " min | Host: " << host << "\n";
}

std::unique_ptr<Media> Podcast::clone() const {
    return std::make_unique<Podcast>(*this);
}
