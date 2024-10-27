#include "CardSelector.h"

#include <iostream>
#include <thread>

using namespace std;

CardSelector::CardSelector(const shared_ptr<BackupService> &backupService, const shared_ptr<BoardManager> &boardManager,
                           const shared_ptr<UserManager> &userManager)
	: backupService(backupService), boardManager(boardManager), userManager(userManager) {
}

CardSelection CardSelector::selectCards(const shared_ptr<User> &user, const Board &board) {
	CardSelection selection;
	selection.isValid = false;
	selection.requestedSave = false;

	const int firstCard = getValidCardNumber(user, "pierwszej", board, -1);
	if (firstCard == -1) {
		selection.requestedSave = true;
		return selection;
	}

	boardManager->printBoardWithRevealedCard(make_shared<Board>(board), firstCard);

	const int secondCard = getValidCardNumber(user, "drugiej", board, firstCard);
	if (secondCard == -1) {
		selection.requestedSave = true;
		return selection;
	}

	boardManager->printBoardWithRevealedCards(make_shared<Board>(board), firstCard, secondCard);

	if (user->getName() == "Komputer") {
		this_thread::sleep_for(chrono::milliseconds(1000));
	}

	selection.firstCardIndex = firstCard;
	selection.secondCardIndex = secondCard;
	selection.isValid = true;

	return selection;
}

int CardSelector::getValidCardNumber(const shared_ptr<User> &user, const string &cardOrder, const Board &board,
                                     const int firstCard = -1) {
	const bool isComputer = user->getName() == "Komputer";

	if (isComputer) {
		cout << "Komputer wybiera " << cardOrder << " karte..." << endl;
		this_thread::sleep_for(chrono::milliseconds(1300));
		return getComputerCardChoice(board, firstCard);
	}

	string input;
	while (true) {
		cout << "Podaj numer " << cardOrder << " karty (lub !zapisz, aby zapisac stan gry): ";
		cin >> input;

		if (input == "!zapisz") {
			backupService->saveBoardToFile(make_shared<Board>(board), user, userManager->getUsers());
			return -1;
		}

		try {
			const int cardNumber = stoi(input);
			if (validateCardNumber(cardNumber - 1, board, firstCard)) {
				return cardNumber - 1;
			}
		} catch(...) {
			cout << "Nieprawidlowy numer karty! Wybierz ponownie." << endl;
		}
	}
}

bool CardSelector::validateCardNumber(const int number, const Board &board, const int firstCard = -1) const {
	if (number < 0 || number >= board.getCards().size()) {
		cout << "Nieprawidlowy numer karty! Wybierz ponownie." << endl;
		return false;
	}

	if (board.getCard(number).has_value() && board.getCard(number)->isGuessed()) {
		cout << "Karta jest juz odgadnieta! Wybierz ponownie." << endl;
		return false;
	}

	if (firstCard != -1 && number == firstCard) {
		cout << "Nie mozna wybrac tej samej karty! Wybierz ponownie." << endl;
		return false;
	}

	return true;
}

int CardSelector::getComputerCardChoice(const Board &board, const int firstCard = -1) {
	vector<int> availableCards;

	for (int i = 0; i < board.getCards().size(); i++) {
		if (!board.getCard(i)->isGuessed() && i != firstCard) {
			availableCards.push_back(i);
		}
	}

	if (availableCards.empty()) {
		throw runtime_error("No cards available");
	}

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(0, availableCards.size() - 1);

	return availableCards[dist(gen)];
}