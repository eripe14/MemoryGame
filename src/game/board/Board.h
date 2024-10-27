#ifndef BOARD_H
#define BOARD_H
#include "../user/User.h"

#include <map>
#include "card/Card.h"
#include "card/CardTypeService.h"
#include "difficulty/Difficulty.h"

#include <memory>
#include <optional>

using namespace std;

class Board {
  private:
    map<int, Card> cards;
    const int rows;
    const int cols;
    const Difficulty difficulty;
	vector<shared_ptr<User>> temporaryUsers;

  public:
    Board(const int rows, const int cols, const Difficulty difficulty);
    Board(const int rows, const int cols, const Difficulty difficulty, const vector<shared_ptr<User>> &temporaryUsers);

    map<int, Card> getCards() const;

	optional<Card> getCard(const int cardNumber) const;

    Card* getCardNonOptional(const int cardNumber);

	void createCards(const CardTypeService &cardTypeService, const Difficulty &difficulty);

	void addCard(const Card card);

    int getRows() const;

    int getCols() const;

    Difficulty getDifficulty() const;

	void addTemporaryUser(const shared_ptr<User> &user);

	vector<shared_ptr<User>> getTemporaryUsers() const;
};

#endif //BOARD_H