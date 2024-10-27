#ifndef TURNQUEUE_H
#define TURNQUEUE_H
#include "../../user/UserManager.h"

#include <vector>

class TurnQueue {
	private:
		shared_ptr<UserManager> userManager;
		vector<string> userOrder;
		int currentUserIndex = 0;

	public:
		TurnQueue(const shared_ptr<UserManager> &userManager);

		void addUser(const string &username);

		void nextTurn();

		void setCurrentUser(const shared_ptr<User> &user);

		shared_ptr<User> getCurrentUser();

		bool isEmpty() const;
};

#endif //TURNQUEUE_H