#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "board/Board.h"

class GameState {
	public:
		bool isGameOver() const;
		void update(const Board& board);

	private:
		bool gameOver = false;
};

#endif //GAMESTATE_H
