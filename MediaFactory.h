// MediaFactory.h
#ifndef MEDIA_FACTORY_H
#define MEDIA_FACTORY_H

#include "Media.h"
#include <map>
#include <functional>

// Factory Method Pattern + Singleton Pattern
class MediaFactory {
private:
    MediaFactory() = default;
    std::map<std::string, std::function<std::unique_ptr<Media>(const std::string&, double, const std::string&)>> creators;

public:
    static MediaFactory& getInstance() {
        static MediaFactory instance;
        return instance;
    }

    void registerCreator(const std::string& type,
                        std::function<std::unique_ptr<Media>(const std::string&, double, const std::string&)> creator) {
        creators[type] = creator;
    }

    std::unique_ptr<Media> createMedia(const std::string& type, const std::string& title,
                                     double duration, const std::string& details) {
        auto it = creators.find(type);
        if (it == creators.end()) {
            throw MediaLibraryException("Unknown media type: " + type);
        }
        return it->second(title, duration, details);
    }
};

#endif