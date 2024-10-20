#include "BackupService.h"

#include "../user/UserManager.h"

#include <ctime>
#include <fstream>
#include <future>
#include <iostream>

using namespace std;

void BackupService::saveBoardToFile(const Board &board, const UserManager &userManager) {
	const string fileName = "./resources/xd.txt";

	// Nazwałem to od nazwy klasy CompletableFuture z Javy (pozwala na async operacje), w której piszę stale od 5 lat ;)
	auto completableFuture = async(launch::async, [this, &board, fileName, &userManager]() {
		ofstream file(fileName);

		if (!file) {
			cerr << "Nie udalo sie zapisac pliku z stanem gry!" << endl;
			return;
		}

		file << board.getRows() << " " << board.getCols() << " " << board.getDifficulty() << endl;

		for (const pair<int, Card> pair : board.getCards()) {
			const Card card = pair.second;
			file << card.getNumber() << " " << card.getCardType() << " " << card.isGuessed() << endl;
		}

		unordered_map<string, shared_ptr<User>> users = userManager.getUsers();

		for (auto pair : users) {
			shared_ptr<User> user = pair.second;
			file << user->getName() << " " << user->getPoints() << endl;
		}

		file.close();
	});
}

Board BackupService::loadBoardFromFile(const string &fileName, UserManager &userManager) {
	ifstream file(fileName);

	if (!file) {
		cerr << "Nie udalo sie wczytac pliku z zapisem gry!" << endl;
		return Board(0, 0, Difficulty::EASY);
	}

	int rows, cols, difficulty;
	file >> rows >> cols >> difficulty;
	Board board(rows, cols, static_cast<Difficulty>(difficulty));

	int cardNumber;
	string cardType;
	bool isGuessed;
	while (file >> cardNumber >> cardType >> isGuessed) {
		const Card card(cardNumber, cardType, isGuessed);
		board.addCard(card);
	}

	cout << "2" << endl;

	string userName;
	int points;
	while (file >> userName >> points) {
		cout << "Reading user: " << userName << " with points: " << points << endl; // Debug output
		const auto user = make_shared<User>(userName, points);

		cout << "Wczytano gracza " << user->getName() << " z " << user->getPoints() << " punktami" << endl;
		userManager.addUser(user);
	}

	file.close();
	return board;
}

string BackupService::getBackupFileName() const {
	time_t timestamp;
	time(&timestamp);

	return "backup_" + to_string(timestamp) + ".txt";
}