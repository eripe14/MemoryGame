#ifndef BOARD_H
#define BOARD_H
#include <map>
#include "card/Card.h"
#include "card/CardTypeService.h"
#include "difficulty/Difficulty.h"

using namespace std;

class Board {
  private:
    map<int, Card> cards;
    const int rows;
    const int cols;
    const Difficulty difficulty;

  public:
    Board(const int rows, const int cols, const Difficulty difficulty);

    map<int, Card> getCards() const;

	Card* getCard(const int cardNumber);

	void createCards(const CardTypeService &cardTypeService, const Difficulty &difficulty);

	void addCard(const Card card);

    int getRows() const;

    int getCols() const;

    Difficulty getDifficulty() const;
};

#endif //BOARD_H