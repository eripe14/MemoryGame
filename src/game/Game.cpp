#include "Game.h"
#include <thread>
#include <chrono>
#include <iostream>

Game::Game(shared_ptr<UserManager> userManager,
           shared_ptr<Board> board,
           shared_ptr<BackupService> backupService,
           shared_ptr<BoardManager> boardManager,
           shared_ptr<AchievementManager> achievementManager)
    : userManager(userManager)
    , board(board)
    , backupService(backupService)
	, boardManager(boardManager)
	, achievementManager(achievementManager)
    , turnQueue(make_unique<TurnQueue>(userManager))
    , scoreManager(make_unique<ScoreManager>(achievementManager))
    , cardSelector(make_unique<CardSelector>(backupService, boardManager, userManager)) {

	startTime = chrono::steady_clock::now();

	if (!board->getTemporaryUsers().empty()) {
		for (shared_ptr<User> temporaryUser : board->getTemporaryUsers()) {
			optional<User> userOptional = userManager->loadUser(temporaryUser->getName());
			if (userOptional.has_value() && userOptional.value().getName() == temporaryUser->getName()) {
				userManager->addUser(make_shared<User>(userOptional.value()));
				continue;
			}

			userManager->addUser(temporaryUser);
		}
	}

	for (const auto &pair : userManager->getUsers()) {
		turnQueue->addUser(pair.first);
	}
}

bool Game::isGameOver() {
	const map<int, Card> cards = board->getCards();
	return all_of(cards.begin(), cards.end(), [](const auto &pair) {
		return pair.second.isGuessed();
	});;
}

void Game::startGame(optional<string> currentUser) {
    boardManager->clearBoard();
    boardManager->printBoard(board);

    if (currentUser.has_value()) {
    	User user = userManager->getUser(currentUser.value());
	    turnQueue->setCurrentUser(make_shared<User>(user));
    }

    while (!isGameOver()) {
        if (turnQueue->isEmpty()) {
            cerr << "Brak graczy w grze." << endl;
            return;
        }

        playRound();
    	turnQueue->nextTurn();
    }

	scoreManager->updateScores(userManager->getUsers());
	scoreManager->displayFinalScores();
	for (const auto pair : userManager->getUsers()) {
		shared_ptr<User> user = pair.second;
		userManager->saveUser(*user);
	}
	userManager->clearUsers();
}

void Game::playRound() {
	const auto currentPlayer = turnQueue->getCurrentUser();

    if (!currentPlayer) {
        cout << "Blad: brak gracza!" << endl;
        return;
    }

    cout << ANSI_GREEN << "Ruch gracza: " << ANSI_BOLD_YELLOW << currentPlayer->getName() << ANSI_RESET << endl;

    bool continueTurn = true;
    while (continueTurn && !isGameOver()) {
        continueTurn = processPlayerMove(currentPlayer);
    }
}

bool Game::processPlayerMove(const shared_ptr<User>& currentUser) {
	const auto selection = cardSelector->selectCards(currentUser, *board);

    if (!selection.isValid) {
        return true;
    }

    if (selection.requestedSave) {
        return true;
    }

    return handleCardSelection(selection);
}

bool Game::handleCardSelection(const CardSelection& cardSelection) {
    Card* firstCard = board->getCardNonOptional(cardSelection.firstCardIndex);
    Card* secondCard = board->getCardNonOptional(cardSelection.secondCardIndex);

    boardManager->printBoardWithRevealedCards(board, cardSelection.firstCardIndex, cardSelection.secondCardIndex);
    this_thread::sleep_for(chrono::milliseconds(1500));

	const auto currentPlayer = turnQueue->getCurrentUser();
	UserGameStats userGameStats = currentPlayer->getGameStats();
    if (firstCard->getCardType() == secondCard->getCardType()) {
    	userGameStats.addPairFound();
        currentPlayer->addPoints(1);

    	currentPlayer->setGameStats(userGameStats);
    	userManager->addUser(currentPlayer);

        firstCard->setGuessed(true);
        secondCard->setGuessed(true);
    	board->addCard(*firstCard);
    	board->addCard(*secondCard);

    	boardManager->clearBoard();
    	boardManager->printBoard(board);

        cout << ANSI_GREEN << "Gracz " << currentPlayer->getName() << " zdobywa punkt (" << currentPlayer->getPoints() << ")!" << ANSI_RESET << endl;

        return true;
    }

	userGameStats.addMistake();
	currentPlayer->setGameStats(userGameStats);
	userManager->addUser(currentPlayer);

	boardManager->clearBoard();
    boardManager->printBoard(board);
    cout << ANSI_RED << "Brak pary, ruch sie skonczyl." << ANSI_RESET << endl;
    return false;
}