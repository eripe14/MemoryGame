#ifndef USERSTATISTICS_H
#define USERSTATISTICS_H
#include <string>

using namespace std;

class UserStatistics {
	private:
		const string userName;
		int gameWon;
		int gameLost;
		int gameDraw;

	public:
		explicit UserStatistics(const string &userName);

		UserStatistics(const string &userName, const int gameWon, const int gameLost, const int gameDraw);

		string getUserName() const;

		int getGameWon() const;

		int getGameLost() const;

		int getGameDraw() const;

		void addGameWon();

		void addGameLost();

		void addGameDraw();

		void updateStatistics(const int won, const int lost, const int draw);
};

#endif //USERSTATISTICS_H
