#include "User.h"

#include "../achievement/AchievementManager.h"

#include <iostream>

User::User(const string &name, const UserStatistics &statistics, const int points)
	: name(name), statistics(statistics), points(points), gameStats(UserGameStats(0, 0)) {
}

User::User(const string &name, const UserStatistics &statistics, const UserGameStats &gameStats, const int points)
	: name(name), statistics(statistics), gameStats(gameStats), points(points) {
}

User::User(const string &name, const UserStatistics &statistics)
	: name(name), statistics(statistics), gameStats(UserGameStats(0, 0)), points(0) {
}

string User::getName() const {
	return name;
}

UserStatistics User::getStatistics() const {
	return statistics;
}

void User::setStatistics(const UserStatistics &other) {
	statistics.updateStatistics(
		other.getGameWon(),
		other.getGameLost(),
		other.getGameDraw()
	);
}

int User::getPoints() const {
	return points;
}

void User::addPoints(const int points) {
	this->points += points;
}

UserGameStats User::getGameStats() const {
	return gameStats;
}

void User::setGameStats(const UserGameStats &stats) {
	gameStats.updateStats(
		stats.getPairsFound(),
		stats.getMistakes()
	);
}

void User::unlockAchievement(const Achievement &achievement) {
	unlockedAchievements.insert({achievement.getName(), achievement});
}

void User::printAchievements() const {
	cout <<	"------------------------" << endl;
	cout << ANSI_BOLD_YELLOW << "Odblokowane osiagniecia: " << ANSI_RESET << endl;

	if (unlockedAchievements.empty()) {
		cout << ANSI_RED << "Brak odblokowanych osiagniec." << ANSI_RESET << endl;
		cout << "------------------------" << endl << endl;
		return;
	}

	int i = 1;
	for (const auto &pair : unlockedAchievements) {
		cout << i << ". " << ANSI_GREEN << pair.second.getName() << ANSI_RESET << endl << pair.second.getDescription() << endl;
		cout << "------------------------" << endl;
		i++;
	}

	cout << endl;
}

int User::getGamePlayed() const {
	const int gameWon = statistics.getGameWon();
	const int gameLost = statistics.getGameLost();
	const int gameDraw = statistics.getGameDraw();

	return gameDraw + gameLost + gameWon;
}

bool User::hasAchievement(const string &name) const {
	return unlockedAchievements.contains(name);
}

unordered_map<string, Achievement> User::getUnlockedAchievements() const {
	return unlockedAchievements;
}