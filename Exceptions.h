// CustomExceptions.h
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class MediaLibraryException : public std::exception {
protected:
    std::string message;
public:
    MediaLibraryException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class MediaNotFoundException : public MediaLibraryException {
public:
    MediaNotFoundException(const std::string& title)
        : MediaLibraryException("Media not found: " + title) {}
};

class UserNotFoundException : public MediaLibraryException {
public:
    UserNotFoundException(const std::string& username)
        : MediaLibraryException("User not found: " + username) {}
};

class FileOperationException : public MediaLibraryException {
public:
    FileOperationException(const std::string& operation)
        : MediaLibraryException("File operation failed: " + operation) {}
};

class InvalidDurationException : public MediaLibraryException {
public:
    InvalidDurationException(double duration)
        : MediaLibraryException("Invalid duration value: " + std::to_string(duration)) {}
};

#endif // CUSTOM_EXCEPTIONS_H