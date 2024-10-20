#include "Board.h"

#include "difficulty/Difficulty.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <set>
#include <unordered_set>

using namespace std;

Board::Board(const int rows, const int cols, const Difficulty difficulty) : rows(rows), cols(cols), difficulty(difficulty) {}

map<int, Card> Board::getCards() const {
    return cards;
}

Card* Board::getCard(const int cardNumber) {
	for (auto& pair : cards) {
		Card& card = pair.second;

		if (card.getNumber() == cardNumber) {
			return &card;
		}
	}

	return nullptr;
}

void Board::createCards(const CardTypeService &cardTypeService, const Difficulty &difficulty) {
	const int totalCards = cols * rows;
	const int pairsCount = totalCards / 2;

	vector<Card> cards;
	cards.reserve(totalCards);

	unordered_set<string> uniqueCardTypes;
	uniqueCardTypes.reserve(pairsCount);

	while (uniqueCardTypes.size() < pairsCount) {
		uniqueCardTypes.insert(cardTypeService.getCardType(difficulty));
	}

	// Przygotowanie wektora indeksów
	vector<int> availableIndices(totalCards);
	iota(availableIndices.begin(), availableIndices.end(), 0); // Wypełnia od 0 do totalCards - 1

	// Losowe indeksowanie kart
	random_device rd;
	mt19937 g(rd());

	// Tworzenie par kart i losowe przypisywanie im indeksów
	for (const auto& type : uniqueCardTypes) {
		shuffle(availableIndices.begin(), availableIndices.end(), g);
		int firstIndex = availableIndices.back();
		availableIndices.pop_back();

		shuffle(availableIndices.begin(), availableIndices.end(), g);
		int secondIndex = availableIndices.back();
		availableIndices.pop_back();

		// Umieszczanie pary na losowych pozycjach w wektorze kart
		cards.emplace_back(firstIndex, type);
		cards.emplace_back(secondIndex, type);
	}

	for (const auto& card : cards) {
		addCard(card);
	}
}

void Board::addCard(const Card card) {
    cards.insert(pair(card.getNumber(), card));
}

int Board::getRows() const {
    return rows;
}

int Board::getCols() const {
    return cols;
}

Difficulty Board::getDifficulty() const {
    return difficulty;
}