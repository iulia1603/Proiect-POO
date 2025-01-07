#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>

class User {
private:
    std::string username;
    std::string email;

public:
    User(const std::string& username, const std::string& email) : username(username), email(email) {}

    const std::string& getUsername() const { return username; }
    const std::string& getEmail() const { return email; }

    void display() const; // Afișează detalii despre utilizator
};

#endif // USER_H
