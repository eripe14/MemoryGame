#include "BackupService.h"

#include "../achievement/AchievementManager.h"
#include "../user/UserManager.h"

#include <ctime>
#include <fstream>
#include <future>
#include <iostream>
#include <filesystem>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

filesystem::path BackupService::getFolderPath() const {
	filesystem::path resourcesPath = getPath() / "resources";
	filesystem::create_directory(resourcesPath);
	filesystem::create_directory(resourcesPath / "users");
	return resourcesPath;
}

vector<string> BackupService::getBackupFiles() const {
	const filesystem::path folderPath = getFolderPath();
	vector<string> files;

	if (!filesystem::exists(folderPath) || !filesystem::is_directory(folderPath)) {
		cout << "Folder nie istnieje!" << endl;
		return files;
	}

	for (const auto &entry : filesystem::directory_iterator(folderPath)) {
		if (!entry.is_regular_file()) {
			continue;
		}

		string fileName = entry.path().filename().string();
		files.push_back(fileName);
	}

	return files;
}

void BackupService::saveBoardToFile(
	const shared_ptr<Board> &board,
	const shared_ptr<User> &currentUser,
	const unordered_map<string, shared_ptr<User>> &users) const {
	const string fileName = getBackupFileName(getFolderPath());

	auto completableFuture = async(launch::async, [this, &board, fileName, &currentUser, users]() {
		ofstream file(fileName);

		if (!file) {
			cerr << "Nie udalo sie zapisac pliku z stanem gry!" << endl;
			return;
		}

		json jsonData;
		jsonData["rows"] = board->getRows();
		jsonData["cols"] = board->getCols();
		jsonData["difficulty"] = board->getDifficulty();
		jsonData["currentUser"] = currentUser->getName();
		jsonData["users"] = json::array();

		for (const pair<int, Card> &pair: board->getCards()) {
			const Card &card = pair.second;
			json cardJson = {{"number", card.getNumber()}, {"type", card.getCardType()}, {"guessed", card.isGuessed()}};
			jsonData["cards"].push_back(cardJson);
		}

		for (const auto pair: users) {
			const shared_ptr<User> user = pair.second;
			const UserGameStats& gameStats = user->getGameStats();

			jsonData["users"].push_back({
				{"name", user->getName()},
				{"points", user->getPoints()},
				{"gameStats", {
					{"pairsFound", gameStats.getPairsFound()},
					{"mistakes", gameStats.getMistakes()}
				}}
			});
		}

		file << jsonData.dump(4);
		file.close();
		cout << ANSI_GREEN << "Zapisano stan gry do pliku: " << ANSI_BOLD_YELLOW << fileName << ANSI_RESET << endl;
	});

}

pair<shared_ptr<Board>, string>  BackupService::loadBoardFromFile(const string &fileName) const {
	filesystem::path resourcesPath = getFolderPath();
	ifstream file(resourcesPath / fileName);

	if (!file) {
		cerr << "Nie udalo sie wczytac pliku z zapisem gry!" << endl;
		return pair<shared_ptr<Board>, string>(make_shared<Board>(0, 0, Difficulty::EASY), "");
	}

	json jsonData;
	file >> jsonData;

	int rows = jsonData["rows"];
	int cols = jsonData["cols"];
	int difficulty = jsonData["difficulty"];
	string currentUser = jsonData["currentUser"];
	vector<shared_ptr<User>> users;

	for (const auto &userJson : jsonData["users"]) {
		string name = userJson["name"];
		int points = userJson["points"];

		int pairsFound = userJson["gameStats"]["pairsFound"];
		int mistakes = userJson["gameStats"]["mistakes"];
		cout << "pairsFound: " << pairsFound << " mistakes: " << mistakes << endl;
		UserGameStats gameStats(pairsFound, mistakes);

		string dummy;
		cin >> dummy;

		auto user = make_shared<User>(name, UserStatistics(name), gameStats, points);
		users.push_back(user);
	}

	auto board = make_shared<Board>(rows, cols, static_cast<Difficulty>(difficulty), users);

	for (const auto &cardJson : jsonData["cards"]) {
		int number = cardJson["number"];
		string type = cardJson["type"];
		bool guessed = cardJson["guessed"];
		board->addCard(Card(number, type, guessed));
	}

	file.close();
	return pair<shared_ptr<Board>, string>(board, currentUser);
}

string DateTime(const time_t time, const char *format) {
	char buffer[90];
	const struct tm *timeinfo = localtime(&time);

	strftime(buffer, sizeof(buffer), format, timeinfo);
	return buffer;
}

string BackupService::getBackupFileName(filesystem::path path) const {
	time_t timestamp;
	time(&timestamp);

	const auto format = "%Y_%m_%d_%H_%M_%S";
	const string formattedTime = DateTime(timestamp, format);

	return (path / ("backup_" + formattedTime + ".json")).string();
}


