#include "TurnQueue.h"
#include <iostream>

TurnQueue::TurnQueue(UserManager &userManager) : userManager(userManager), currentUserIndex(0) {}

void TurnQueue::addUser(const string &name) {
	if (userManager.getUser(name).getName() != "") {
		userOrder.push_back(name);
		cout << "Dodano gracza " << name << endl;
	}

	cout << "Nie znaleziono gracza " << name << endl;
}

void TurnQueue::nextTurn() {
	if (userOrder.empty()) {
		return;
	}

	currentUserIndex = (currentUserIndex + 1) % userOrder.size();
}

shared_ptr<User> TurnQueue::getCurrentUser() {
	if (userOrder.empty()) {
		return nullptr;
	}

	const string currentUserName = userOrder[currentUserIndex];
	return make_shared<User>(userManager.getUser(currentUserName));
}

bool TurnQueue::isEmpty() const {
	return userOrder.empty();
}