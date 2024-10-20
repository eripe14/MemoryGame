#include "game/Game.h"
#include "game/backup/BackupService.h"

#include <iostream>

#include "game/board/Board.h"
#include "game/board/BoardManager.h"
#include "game/board/SizeProvider.h"
#include "game/board/card/Card.h"
#include "game/board/card/CardTypeService.h"
#include "game/board/difficulty/DifficultyProvider.h"
#include "game/user/UserManager.h"
#include "game/user/UserProvider.h"

#include <fstream>
#include <filesystem>
using namespace std;

int main() {

	/*
	*	BackupService backupService;


	Board board = backupService.loadBoardFromFile("xd.txt", userManager);
	cout << "Wczytano plansze" << endl;

	cout << board.getRows() << " " << board.getCols() << " " << to_string(board.getDifficulty()) << endl;
	cout << "size: " << userManager.getUsers().size() << endl;

	for (auto user : userManager.getUsers()) {
		cout << user.second->getName() << " " << user.second->getPoints() << endl;
	}

	string dummy;
	cin >> dummy;

	 */

	filesystem::current_path("../");
	filesystem::create_directories("./resources");

	UserManager userManager;
	const UserProvider userProvider(userManager);
	userProvider.provideUsers();

	const DifficultyProvider difficultyProvider = DifficultyProvider();
	const Difficulty difficulty = difficultyProvider.getDifficulty();
	const CardTypeService cardTypeService = CardTypeService();
	const pair<int, int> boardSize = SizeProvider::getBoardSize();

	Board board = Board(boardSize.first, boardSize.second, difficulty);
	board.createCards(cardTypeService, difficulty);



	// kolory dodac:
	// zielony odkryte, zolty w trakcie odkrywania

	Game game = Game(userManager, board);
	game.startGame();

	return 0;
}