#include "Game.h"

#include "backup/BackupService.h"

#include <algorithm>
#include <iostream>
#include <thread>

Game::Game(UserManager &userManager, Board &board)
	: userManager(userManager), turnQueue(userManager), boardManager(),
	  board(board) {

	for (const auto &pair : userManager.getUsers()) {
		turnQueue.addUser(pair.first);
	}
}

void Game::startGame() {
	boardManager.clearBoard();
	boardManager.printBoard(board);

	while (!isGameOver()) {
		if (turnQueue.isEmpty()) {
			cout << "Brak graczy w grze." << endl;
			return;
		}

		takeTurn();
		turnQueue.nextTurn();
	}

	displayScores();
}

void Game::takeTurn() {
	const shared_ptr<User> user = turnQueue.getCurrentUser();

	if (!user) {
		cout << "Błąd: Brak aktualnego gracza!" << endl;
		return;
	}

	cout << "Ruch gracza " << user->getName() << endl;

	const bool isComputer = user->getName() == "Komputer";
	bool continueTurn = true;

	while (continueTurn && !isGameOver()) {
		int firstCardNumber;
		int secondCardNumber;

		if (isComputer) {
			cout << "Komputer wybiera numer pierwszej karty: " <<firstCardNumber << endl;
			this_thread::sleep_for(chrono::seconds(2));
			firstCardNumber = getRandomCardNumber();
		} else {
			cout << "Podaj numer pierwszej karty: ";
			cin >> firstCardNumber;
		}

		if (firstCardNumber < 1 || firstCardNumber > board.getCards().size()) {
			cout << "Nieprawidłowy numer karty! Wybierz ponownie." << endl;
			continue;
		}

		Card *firstCard = board.getCard(firstCardNumber - 1);
		if (firstCard == nullptr || firstCard->getNumber() > board.getCards().size()) {
			cout << "Nie znaleziono karty o numerze " << firstCardNumber <<
				endl;
			continue;
		}

		boardManager.printBoardWithRevealedCard(board, firstCardNumber);
		cout << "Odkryto karte: " << firstCard->getCardType() << endl;

		if (isComputer) {
			cout << "Komputer wybiera numer drugiej karty: " << secondCardNumber << endl;
			this_thread::sleep_for(chrono::seconds(1));
			secondCardNumber = getRandomCardNumber();

		} else {
			cout << "Podaj numer drugiej karty: ";
			cin >> secondCardNumber;
		}

		if (secondCardNumber < 1 || secondCardNumber > board.getCards().
		    size()) {
			cout << "Nieprawidłowy numer karty! Wybierz ponownie." << endl;
			continue;
		}

		Card *secondCard = board.getCard(secondCardNumber - 1);
		if (secondCard == nullptr || secondCard->getNumber() > board.getCards().
		    size()) {
			cout << "Nie znaleziono karty o numerze " << secondCardNumber <<
				endl;
			continue;
		}

		boardManager.printBoardWithRevealedCards(
			board, firstCardNumber, secondCardNumber);

		if (firstCard->getCardType() == secondCard->getCardType()) {
			User pointsUser = userManager.getUser(user->getName());
			pointsUser.addPoints(1);
			userManager.addUser(make_shared<User>(pointsUser));

			firstCard->setGuessed(true);
			secondCard->setGuessed(true);

			board.addCard(*firstCard);
			board.addCard(*secondCard);

			boardManager.clearBoard();
			boardManager.printBoard(board);
			cout << "Gracz " << user->getName() << " zdobywa punkt (" << pointsUser.getPoints() << ")!" << endl;
		} else {
			cout << "Gracz " << user->getName() << " nie zdobywa punktu." <<
				endl;
			continueTurn = false; // Zakończ turę, jeśli karty się nie zgadzały
		}
	}
}


bool Game::isGameOver() const {
	const map<int, Card> cards = board.getCards();
	return all_of(cards.begin(), cards.end(), [](const auto &pair) {
		return pair.second.isGuessed();
	});;
}

void Game::displayScores() const {
	cout << "Final scores:" << endl;
	for (auto user : userManager.getUsers()) {
		const shared_ptr<User> shared_ptr = user.second;
		cout << shared_ptr->getName() << " : " << shared_ptr->getPoints() <<
			endl;
	}

	BackupService backupService;
	backupService.saveBoardToFile(board, userManager);

	string dummy;
	cin >> dummy;
}

int Game::getRandomCardNumber() const {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, board.getCards().size());

	return dist(gen);
}