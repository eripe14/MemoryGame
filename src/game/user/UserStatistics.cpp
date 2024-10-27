#include "UserStatistics.h"

UserStatistics::UserStatistics(const string &userName)
	: userName(userName), gameWon(0), gameLost(0), gameDraw(0) {}

UserStatistics::UserStatistics(const string &userName, const int gameWon, const int gameLost, const int gameDraw)
	: userName(userName), gameWon(gameWon), gameLost(gameLost), gameDraw(gameDraw) {}

string UserStatistics::getUserName() const {
	return userName;
}

int UserStatistics::getGameWon() const {
	return gameWon;
}

int UserStatistics::getGameLost() const {
	return gameLost;
}

int UserStatistics::getGameDraw() const {
	return gameDraw;
}

void UserStatistics::addGameWon() {
	gameWon++;
}

void UserStatistics::addGameLost() {
	gameLost++;
}

void UserStatistics::addGameDraw() {
	gameDraw++;
}

void UserStatistics::updateStatistics(const int won, const int lost, const int draw) {
	gameWon  = won;
	gameLost = lost;
	gameDraw = draw;
}