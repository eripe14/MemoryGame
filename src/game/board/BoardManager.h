#ifndef BOARDMANAGER_H
#define BOARDMANAGER_H
#include <stdlib.h>

#include "Board.h"

#include <memory>

using namespace std;

class BoardManager {
public:
    void clearBoard();

    void printBoard(const shared_ptr<Board> &board);

	void printBoardWithRevealedCard(const shared_ptr<Board> &board, const int &cardNumber);

	void printBoardWithRevealedCards(const shared_ptr<Board> &board, const int &firstCardNumber, const int &secondCardNumber);
};

#endif
