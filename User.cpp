#include "User.h"
#include <iostream>

// Afișează detalii despre utilizator
void User::display() const {
    std::cout << "User: " << username << " | Email: " << email << "\n";
}
