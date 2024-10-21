#ifndef GAME_H
#define GAME_H
#include "../game/board/BoardManager.h"
#include "../game/board/queue/TurnQueue.h"
#include "../game/user/UserManager.h"

class Game {
	private:
		UserManager &userManager;
		TurnQueue turnQueue;
		BoardManager boardManager;
		Board &board;
	public:
		Game(UserManager &userManager, Board &board);

		void startGame();

		void takeTurn();

		bool isGameOver() const;

		void displayScores() const;

		int getRandomCardNumber() const;
};

#endif //GAME_H