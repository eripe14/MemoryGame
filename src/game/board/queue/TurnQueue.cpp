#include "TurnQueue.h"
#include <iostream>


TurnQueue::TurnQueue(const shared_ptr<UserManager> &userManager) : userManager(userManager) {
}

void TurnQueue::addUser(const string &name) {
	if (userManager->getUser(name).getName() != "") {
		userOrder.push_back(name);
		return;
	}

	cout << "Nie znaleziono gracza " << name << endl;
}

void TurnQueue::nextTurn() {
	if (userOrder.empty()) {
		return;
	}

	currentUserIndex = (currentUserIndex + 1) % userOrder.size();
}

void TurnQueue::setCurrentUser(const shared_ptr<User> &user) {
	if (user == nullptr) {
		return;
	}

	for (size_t i = 0; i < userOrder.size(); ++i) {
		if (userOrder[i] == user->getName()) {
			currentUserIndex = i;
			return;
		}
	}

	cout << "Nie znaleziono użytkownika w kolejce!" << endl;
}

shared_ptr<User> TurnQueue::getCurrentUser() {
	if (userOrder.empty()) {
		return nullptr;
	}

	const string currentUserName = userOrder[currentUserIndex];
	return make_shared<User>(userManager->getUser(currentUserName));
}

bool TurnQueue::isEmpty() const {
	return userOrder.empty();
}