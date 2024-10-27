#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H
#include "User.h"
#include "../backup/BackupService.h"

#include <optional>

class BackupService;

class UserRepository {
	private:
		shared_ptr<BackupService> backupService;
	public:
		UserRepository(const shared_ptr<BackupService> &backupService);

		void saveUser(const User &user);

		optional<User> loadUser(const string &username);

		vector<User> loadSavedUsers();

};

#endif //USERREPOSITORY_H