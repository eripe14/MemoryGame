#ifndef USERPROVIDER_H
#define USERPROVIDER_H

#include "UserManager.h"

class UserProvider {
	private:
		UserManager &userManager;

	public:
		explicit UserProvider(UserManager &userManager);
		void provideUsers() const;

	private:
		int provideNumberOfPlayers() const;

		bool isValidNumberOfPlayers(const std::string &input) const;
};

#endif //USERPROVIDER_H