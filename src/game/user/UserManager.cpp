#include "UserManager.h"

UserManager::UserManager(const UserRepository &userRepository) : userRepository(userRepository) {
}

void UserManager::addUser(const shared_ptr<User> &user) {
    users[user->getName()] = user;
}

User UserManager::getUser(const string &name) {
    return *users[name];
}

const unordered_map<string, shared_ptr<User>>& UserManager::getUsers() const {
	return users;
}

void UserManager::saveUser(const User &user) {
	userRepository.saveUser(user);
}

optional<User> UserManager::loadUser(const string &username) {
	return userRepository.loadUser(username);
}

vector<User> UserManager::loadSavedUsers() {
	return userRepository.loadSavedUsers();
}

void UserManager::clearUsers() {
	users.clear();
}