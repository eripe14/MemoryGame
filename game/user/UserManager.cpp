#include "UserManager.h"

void UserManager::addUser(const shared_ptr<User> &user) {
    users[user->getName()] = user;
}

User UserManager::getUser(const string &name) {
    return *users[name];
}

const unordered_map<string, shared_ptr<User>>& UserManager::getUsers() const {
	return users;
}