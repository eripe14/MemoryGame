#ifndef CARDSELECTOR_H
#define CARDSELECTOR_H

#include "backup/BackupService.h"
#include "board/BoardManager.h"
#include "user/UserManager.h"

#include <memory>
#include <string>

using namespace std;

struct CardSelection {
	int firstCardIndex;
	int secondCardIndex;
	bool isValid;
	bool requestedSave;
};

class CardSelector {
	public:
		CardSelector(const shared_ptr<BackupService> &backupService, const shared_ptr<BoardManager> &boardManager, const shared_ptr<UserManager> &userManager);

		CardSelection selectCards(const shared_ptr<User> &user, const Board &board);

	private:
		int getValidCardNumber(const shared_ptr<User> &user, const string &cardOrder, const Board &board, int firstCard);

		int getComputerCardChoice(const Board &board, int firstCard);

		bool validateCardNumber(int number, const Board &board, int firstCard) const;

		shared_ptr<BackupService> backupService;

		shared_ptr<BoardManager> boardManager;

		shared_ptr<UserManager> userManager;

};

#endif //CARDSELECTOR_H