// User.cpp
#include "User.h"
#include <iostream>

void User::display() const {
    std::cout << "User: " << username << " | Email: " << email << "\n";
}

