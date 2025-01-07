#ifndef MEDIA_H
#define MEDIA_H

#include <iostream>
#include <string>
#include <memory>

class Media {
protected:
    //std::string title;
    //double duration;  // in minutes

    std::string title, type;
    double duration;  // in minutes

public:
    Media(const std::string& type, const std::string& title, double duration) : type(type), title(title), duration(duration) {}

    virtual void display() const = 0;
    virtual std::unique_ptr<Media> clone() const = 0;

    const std::string& getType() const { return type; }
    const std::string& getTitle() const { return title; }
    double getDuration() const { return duration; }


    virtual ~Media() = default;
};

class Song : public Media {
    std::string artist;

public:
    Song(const std::string& type, const std::string& title, double duration, const std::string& artist)
            : Media(type, title, duration), artist(artist) {}

    void display() const override;
    std::unique_ptr<Media> clone() const override;
};

class Audiobook : public Media {
    std::string author;

public:
    Audiobook(const std::string& type, const std::string& title, double duration, const std::string& author)
            : Media(type, title, duration), author(author) {}

    void display() const override;
    std::unique_ptr<Media> clone() const override;
};

class Podcast : public Media {
    std::string host;

public:
    Podcast(const std::string& type, const std::string& title, double duration, const std::string& host)
            : Media(type, title, duration), host(host) {}

    void display() const override;
    std::unique_ptr<Media> clone() const override;
};

#endif // MEDIA_H
