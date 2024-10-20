#ifndef BOARDMANAGER_H
#define BOARDMANAGER_H
#include <stdlib.h>

#include "Board.h"

using namespace std;

class BoardManager {
public:
    void clearBoard();

    void printBoard(const Board &board);

	void printBoardWithRevealedCard(const Board &board, const int &cardNumber);

	void printBoardWithRevealedCards(const Board &board, const int &firstCardNumber, const int &secondCardNumber);
};

#endif
