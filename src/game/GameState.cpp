#include "GameState.h"

#include <algorithm>

bool GameState::isGameOver() const {
	return gameOver;
}

void GameState::update(const Board &board) {
	const auto &cards = board.getCards();

	const bool areAllCardsGuessed = all_of(cards.begin(), cards.end(), [](const auto &cardPair) {
		return cardPair.second.isGuessed();
	});

	if (areAllCardsGuessed) {
		gameOver = true;
	}
}