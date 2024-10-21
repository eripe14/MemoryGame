#include "BackupService.h"

#include "../user/UserManager.h"

#include <ctime>
#include <fstream>
#include <future>
#include <iostream>
#include <filesystem>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

void BackupService::saveBoardToFile(const Board &board, const UserManager &userManager) {
	filesystem::current_path("../");
	filesystem::create_directories("./resources");
	const string fileName = getBackupFileName();

	auto completableFuture = async(launch::async, [this, &board, fileName, &userManager]() {
		ofstream file(fileName);

		if (!file) {
			cerr << "Nie udalo sie zapisac pliku z stanem gry!" << endl;
			return;
		}

		json jsonData;
		// Zapisanie planszy
		jsonData["rows"] = board.getRows();
		jsonData["cols"] = board.getCols();
		jsonData["difficulty"] = board.getDifficulty();

		// Zapisanie kart
		for (const pair<int, Card> &pair : board.getCards()) {
			const Card &card = pair.second;
			json cardJson = {{"number", card.getNumber()}, {"type", card.getCardType()}, {"guessed", card.isGuessed()}};
			jsonData["cards"].push_back(cardJson);
		}

		// Zapisanie użytkowników
		unordered_map<string, shared_ptr<User>> users = userManager.getUsers();
		for (const auto &pair : users) {
			shared_ptr<User> user = pair.second;
			json userJson = {{"name", user->getName()}, {"points", user->getPoints()}};
			jsonData["users"].push_back(userJson);
		}

		// Zapis do pliku
		file << jsonData.dump(4); // Zapisuje w ładnym formacie z wcięciami (4 spacje)
		file.close();
	});
}


Board BackupService::loadBoardFromFile(const string &fileName, UserManager &userManager) {
	filesystem::current_path("../");
	ifstream file("./resources/" + fileName);

	if (!file) {
		cerr << "Nie udalo sie wczytac pliku z zapisem gry!" << endl;
		return Board(0, 0, Difficulty::EASY);
	}

	json jsonData;
	file >> jsonData;

	int rows = jsonData["rows"];
	int cols = jsonData["cols"];
	int difficulty = jsonData["difficulty"];
	Board board(rows, cols, static_cast<Difficulty>(difficulty));

	// Odczyt kart
	for (const auto &cardJson : jsonData["cards"]) {
		int number = cardJson["number"];
		string type = cardJson["type"];
		bool guessed = cardJson["guessed"];
		board.addCard(Card(number, type, guessed));
	}

	// Odczyt użytkowników
	for (const auto &userJson : jsonData["users"]) {
		string name = userJson["name"];
		int points = userJson["points"];
		auto user = make_shared<User>(name, points);
		userManager.addUser(user);
	}

	file.close();
	return board;
}




string DateTime(time_t time, const char *format) {
	char buffer[90];
	struct tm *timeinfo = localtime(&time);
	strftime(buffer, sizeof(buffer), format, timeinfo);
	return buffer;
}

string BackupService::getBackupFileName() const {
	time_t timestamp;
	time(&timestamp);

	const char *format = "%Y_%m_%d_%H_%M_%S";
	string formattedTime = DateTime(timestamp, format);

	cout << formattedTime << endl;

	return "./resources/backup_" + formattedTime + ".txt";
}

