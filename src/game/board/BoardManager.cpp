#include "BoardManager.h"

#include <iomanip>
#include <iostream>
#include <memory>

using namespace std;

const string ANSI_RESET  = "\033[0m";
const string ANSI_GREEN  = "\033[32m";
const string ANSI_YELLOW = "\033[33m";

void BoardManager::clearBoard() {
	system("cls");
}

void printLine(const int &cols) {
	for (int c = 0; c < cols; ++c) {
		cout << "-------";
	}
	cout << endl;
}

void printHeader(const int &cols) {
	const int totalWidth = cols * 7;
	const string header = "Memory Game";
	const int padding = (totalWidth - header.length()) / 2;

	printLine(cols);
	cout << setw(padding + header.length()) << header << endl;
	printLine(cols);
}

void printCardLine(const Card &card, const int line, const bool revealCard) {
	const string cardType = card.getCardType();

	if (line == 2) {
		const int cardNumber = card.getNumber() + 1;

		if (card.isGuessed()) {
			cout << "|  " << ANSI_GREEN
				 << (cardType.length() == 3 ? cardType + " "  : cardType.length() == 2 ? cardType + "  " : " " + cardType + "  ")
				 << ANSI_RESET;
			return;
		}

		if (revealCard) {
			cout << "|  " << ANSI_YELLOW << (cardType.length() == 3
				                  ? cardType + " "
				                  : cardType.length() == 2
				                  ? cardType + "  "
				                  : cardType + "   ") << ANSI_RESET;
			return;
		}

		if (cardNumber > 99) {
			cout << "| " << cardNumber << "  "; // Wyrównanie dla trzycyfrowych numerów
			return;
		}

		if (cardNumber > 9) {
			cout << "|  " << cardNumber << "  "; // Wyrównanie dla dwucyfrowych numerów
			return;
		}

		cout << "|   " << cardNumber << "  "; // Wyrównanie dla jednocyfrowych numerów
		return;
	}

	cout << "|      ";
}

void printRow(const map<int, Card> &cards, const int cols, const int row, const int cardNumber) {
	for (int line = 0; line < 5; ++line) {
		for (int c = 0; c < cols; ++c) {
			int cardIndex = row * cols + c;

			if (cards.contains(cardIndex)) {
				const bool revealCard = (cards.at(cardIndex).getNumber() == cardNumber);
				printCardLine(cards.at(cardIndex), line, revealCard);
				continue;
			}

			cout << "|      ";
		}

		cout << "|" << endl;
	}
}

void BoardManager::printBoardWithRevealedCard(const shared_ptr<Board> &board, const int &cardNumber) {
	const map<int, Card> &cards = board->getCards();
	const int cols = board->getCols();
	const int rows = board->getRows();

	clearBoard();
	printHeader(cols);

	for (int r = 0; r < rows; ++r) {
		printRow(cards, cols, r, cardNumber);
		printLine(cols);
	}
}

void BoardManager::printBoardWithRevealedCards(
	const shared_ptr<Board> &board,
	const int &firstCardNumber,
	const int &secondCardNumber) {

	const map<int, Card> &cards = board->getCards();
	const int cols = board->getCols();
	const int rows = board->getRows();

	clearBoard();
	printHeader(cols);

	for (int r = 0; r < rows; ++r) {
		for (int line = 0; line < 5; ++line) {
			for (int c = 0; c < cols; ++c) {
				int cardIndex = r * cols + c;

				if (cards.contains(cardIndex)) {
					const bool revealCard = (cards.at(cardIndex).getNumber() == firstCardNumber ||
					                         cards.at(cardIndex).getNumber() == secondCardNumber);
					printCardLine(cards.at(cardIndex), line, revealCard);
				} else {
					cout << "|      ";
				}
			}
			cout << "|" << endl;
		}
		printLine(cols);
	}
}

void BoardManager::printBoard(const shared_ptr<Board> &board) {
	map<int, Card> cards = board->getCards();
	const int cols = board->getCols();
	const int rows = board->getRows();

	printHeader(cols);

	for (int r = 0; r < rows; ++r) {
		for (int line = 0; line < 5; ++line) {
			for (int c = 0; c < cols; ++c) {
				int cardIndex = r * cols + c;
				const Card card = cards[cardIndex];

				if (cards.contains(cardIndex)) {
					if (line == 0 || line == 1 || line == 3 || line == 4) {
						cout << "|      ";
						continue;
					}

					if (line == 2) {
						printCardLine(card, line, false);
						continue;
					}

					continue;
				}

				cout << "|      ";
			}
			cout << "|" << endl;
		}

		printLine(cols);
	}
}