// Media.h
#ifndef MEDIA_H
#define MEDIA_H

#include "Exceptions.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>

// Observer Pattern - Interface
class MediaObserver {
public:
    virtual ~MediaObserver() = default;
    virtual void onMediaPlayed(const std::string& title) = 0;
};

class Media {
protected:
    std::string title, type;
    double duration;
    std::vector<MediaObserver*> observers;

    virtual void print(std::ostream& os) const = 0;

public:
    Media(const std::string& title, const std::string& type, double duration)
     : title(title), type(type), duration(duration) {
        if (duration < 0) {
            throw InvalidDurationException(duration);
        }
    }

    virtual ~Media() = default;

    virtual void display() const = 0;
    virtual std::unique_ptr<Media> clone() const = 0;

    double getDuration() const { return duration; }
    const std::string& getTitle() const { return title; }

    void addObserver(MediaObserver* observer) {
        observers.push_back(observer);
    }

    void removeObserver(MediaObserver* observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }

    void play() {
        for (auto* observer : observers) {
            observer->onMediaPlayed(title);
        }
    }

    // Member operator overload
    Media& operator+=(double extraDuration) {
        if (extraDuration < 0) {
            throw InvalidDurationException(extraDuration);
        }
        duration += extraDuration;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Media& media);
    friend bool operator==(const Media& lhs, const Media& rhs);
};

// Non-member operator overload
inline bool operator==(const Media& lhs, const Media& rhs) {
    return lhs.title == rhs.title && lhs.type == rhs.type;
}

class Song : public Media {
    std::string artist;

protected:
    void print(std::ostream& os) const override {
        os << type << ": " << title << " | Duration: " << duration << "min | Artist: " << artist << "\n";
    }

public:
    Song(const std::string& title, const std::string& type, double duration, const std::string& artist)
            : Media(title, type, duration), artist(artist) {
        if (duration <= 0) {
            throw InvalidDurationException(duration);
        }
    }

    void display() const override;
    std::unique_ptr<Media> clone() const override;

    // Member operator overload specific to Song
    Song& operator+=(double extraDuration) {
        Media::operator+=(extraDuration);
        return *this;
    }
};

class Audiobook : public Media {
    std::string narrator;

protected:
    void print(std::ostream& os) const override {
        os << type << ": " << title << " | Duration: " << duration << "min | Narrator: " << narrator << "\n";
    }

public:
    Audiobook(const std::string& title, const std::string& type, double duration, const std::string& narrator)
            : Media(title, type, duration), narrator(narrator) {
        if (duration <= 0) {
            throw InvalidDurationException(duration);
        }
    }

    void display() const override;
    std::unique_ptr<Media> clone() const override;

    // Member operator overload specific to Audiobook
    Audiobook& operator+=(double extraDuration) {
        Media::operator+=(extraDuration);
        return *this;
    }
};

class Podcast : public Media {
    std::string host;

protected:
    void print(std::ostream& os) const override {
        os << type << ": " << title << " | Duration: " << duration << "min | Host: " << host << "\n";
    }

public:
    Podcast(const std::string& title, const std::string& type, double duration, const std::string& host)
            : Media(title, type, duration), host(host) {
        if (duration <= 0) {
            throw InvalidDurationException(duration);
        }
    }

    void display() const override;
    std::unique_ptr<Media> clone() const override;

    // Member operator overload specific to Podcast
    Podcast& operator+=(double extraDuration) {
        Media::operator+=(extraDuration);
        return *this;
    }
};

template <class T>
class TemplateMedia : public Media {
    std::string details;
    std::string customInfoName;
    T customInfoValue;

protected:
    void print(std::ostream& os) const override {
        os << type << ": " << title << " | Duration: " << duration << "min | " << details << ": " << customInfoValue << " " << customInfoName << "\n";
    }

public:
    TemplateMedia(const std::string& title, const std::string& type, double duration,
                 const std::string& details, const std::string& customInfoName, const T customInfoValue)
            : Media(title, type, duration), details(details),
              customInfoName(customInfoName), customInfoValue(customInfoValue) {
        if (duration < 0) {
            throw InvalidDurationException(duration);
        }
    }

    void display() const override {
        print(std::cout);
    }

    std::unique_ptr<Media> clone() const override {
        return std::make_unique<TemplateMedia>(*this);
    }

    // Member operator overload specific to TemplateMedia
    TemplateMedia& operator+=(double extraDuration) {
        Media::operator+=(extraDuration);
        return *this;
    }
};

#endif // MEDIA_H