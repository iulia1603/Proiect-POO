// Media.h
#ifndef MEDIA_H
#define MEDIA_H

#include <iostream>
#include <string>
#include <memory>

class Media {
protected:
    std::string title, type;
    double duration;

    virtual void print(std::ostream& os) const = 0;

public:
    Media(const std::string& title, const std::string& type, double duration) : title(title), type(type), duration(duration) {}
    virtual ~Media() = default;

    virtual void display() const = 0;
    virtual std::unique_ptr<Media> clone() const = 0;

    double getDuration() const { return duration; }
    const std::string& getTitle() const { return title; }

    friend std::ostream& operator<<(std::ostream& os, const Media& media);
};

class Song : public Media {
    std::string artist;

protected:
    void print(std::ostream& os) const override {
        os << type << title << " | Duration: " << duration << "min | Artist: " << artist << "\n";
    }

public:
    Song(const std::string& title, const std::string& type, double duration, const std::string& artist)
            : Media(title, type, duration), artist(artist) {}

    void display() const override;
    std::unique_ptr<Media> clone() const override;
};

class Audiobook : public Media {
    std::string narrator;

protected:
    void print(std::ostream& os) const override {
        os << type << title << " | Duration: " << duration << "min | Narrator: " << narrator << "\n";
    }

public:
    Audiobook(const std::string& title, const std::string& type,  double duration, const std::string& narrator)
            : Media(title, type, duration), narrator(narrator) {}

    void display() const override;
    std::unique_ptr<Media> clone() const override;
};

class Podcast : public Media {
    std::string host;

protected:
    void print(std::ostream& os) const override {
        os << type << title << " | Duration: " << duration << "min | Host: " << host << "\n";
    }

public:
    Podcast(const std::string& title, const std::string& type, double duration, const std::string& host)
            : Media(title, type, duration), host(host) {}

    void display() const override;
    std::unique_ptr<Media> clone() const override;
};

template <class T>
class GenericMedia : public Media {
    T details;

protected:
    void print(std::ostream& os) const override {
        os << type << ": " << title << " | Duration: " << duration << "min | " << details << ": " << "\n";
    }

public:
    GenericMedia(const std::string& title, const std::string& type, double duration, const T details)
            : Media(title, type, duration), details(details) {}

    void display() const override {
        print(std::cout);
    }

    std::unique_ptr<Media> clone() const override {
        return std::make_unique<GenericMedia>(*this);
    }
};

#endif // MEDIA_H