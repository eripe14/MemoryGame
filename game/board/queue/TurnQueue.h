#ifndef TURNQUEUE_H
#define TURNQUEUE_H
#include "../../user/UserManager.h"

#include <vector>

class TurnQueue {
	private:
		UserManager userManager;
		vector<string> userOrder;
		int currentUserIndex = 0;

	public:
		TurnQueue(UserManager &userManager);

		void addUser(const string &username);

		void nextTurn();

		shared_ptr<User> getCurrentUser();

		bool isEmpty() const;
};

#endif //TURNQUEUE_H