#include "UserRepository.h"

#include <fstream>
#include <future>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

UserRepository::UserRepository(const shared_ptr<BackupService> &backupService) : backupService(backupService) {
}

void UserRepository::saveUser(const User &user) {
	const filesystem::path path = backupService->getFolderPath();
	const string fileName = (path / "users" / (user.getName() + ".json")).string();

	User userCopy = user;

	auto completableFuture = async(launch::async, [this, userCopy, fileName]() {
		ofstream file(fileName, ios::trunc);

		if (!file) {
			cerr << "Nie udalo sie zapisac pliku z uzytkownikiem " << userCopy.getName() << endl;
			return;
		}

		json jsonData;
		jsonData["name"] = userCopy.getName();
		jsonData["statistics"] = {
			{"gameWon", userCopy.getStatistics().getGameWon()},
			{"gameLost", userCopy.getStatistics().getGameLost()},
			{"gameDraw", userCopy.getStatistics().getGameDraw()}
		};
		jsonData["unlockedAchievements"] = json::array();

		for (const auto &pair : userCopy.getUnlockedAchievements()) {
			jsonData["unlockedAchievements"].push_back({
				{"name", pair.second.getName()},
				{"description", pair.second.getDescription()}
			});
		}

		file << jsonData.dump(4);
		file.close();
		cout << "Zapisano uzytkownika " << userCopy.getName() << endl;
	});
}

optional<User> UserRepository::loadUser(const string &username) {
	filesystem::path resourcesPath = backupService->getFolderPath();
	string fileName = username + ".json";
	ifstream file(resourcesPath / "users" / fileName);

	if (!file) {
		return nullopt;
	}

	try {
		json jsonData;
		file >> jsonData;

		json statisticsData = jsonData["statistics"];
		int gameWon = statisticsData["gameWon"];
		int gameLost = statisticsData["gameLost"];
		int gameDraw = statisticsData["gameDraw"];

		UserStatistics userStatistics(username, gameWon, gameLost, gameDraw);
		User user(username, userStatistics);

		for (const auto &achievementJson : jsonData["unlockedAchievements"]) {
			string name = achievementJson["name"];
			string description = achievementJson["description"];

			Achievement achievement(name, description);
			user.unlockAchievement(achievement);
		}

		file.close();
		return user;
	} catch (const json::exception& exception) {
		return nullopt;
	}
}

vector<User> UserRepository::loadSavedUsers() {
	vector<User> users;
	const filesystem::path usersPath = backupService->getFolderPath() / "users";

	if (!filesystem::exists(usersPath)) {
		return users;
	}

	for (const auto& entry : filesystem::directory_iterator(usersPath)) {
		if (entry.is_regular_file() && entry.path().extension() == ".json") {
			string username = entry.path().stem().string();

			if (optional<User> user = loadUser(username); user.has_value()) {
				users.push_back(user.value());
			}
		}
	}

	return users;
}