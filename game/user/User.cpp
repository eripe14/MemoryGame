#include "User.h"

User::User(const string &name) : name(name), points(0) {}

User::User(const string &name, const int points) : name(name), points(points) {}

string User::getName() const {
    return name;
}

int User::getPoints() const {
    return points;
}

void User::addPoints(const int points) {
    this->points += points;
}