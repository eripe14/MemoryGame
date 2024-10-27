#ifndef GAME_H
#define GAME_H
#include "CardSelector.h"
#include "GameState.h"
#include "../game/board/queue/TurnQueue.h"
#include "../game/user/UserManager.h"
#include "achievement/AchievementManager.h"
#include "backup/BackupService.h"
#include "score/ScoreManager.h"

class Game {
	public:
		Game(
			shared_ptr<UserManager> userManager,
			shared_ptr<Board> board,
			shared_ptr<BackupService> backupService,
			shared_ptr<BoardManager> boardManager,
			shared_ptr<AchievementManager> achievementManager
		);

		void startGame(optional<string> currentUser);

	private:
		chrono::steady_clock::time_point startTime;

		void playRound();

		bool isGameOver();

		bool processPlayerMove(const shared_ptr<User> &currentUser);

		bool handleCardSelection(const CardSelection &cardSelection);

		shared_ptr<UserManager> userManager;
		shared_ptr<Board> board;
		shared_ptr<BackupService> backupService;
		shared_ptr<BoardManager> boardManager;
		shared_ptr<AchievementManager> achievementManager;
		shared_ptr<TurnQueue> turnQueue;
		shared_ptr<ScoreManager> scoreManager;
		shared_ptr<CardSelector> cardSelector;
		GameState gameState;


};

#endif //GAME_H