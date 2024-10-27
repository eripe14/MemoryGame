#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <memory>
#include <unordered_map>
#include <string>
#include "User.h"
#include "UserRepository.h"

using namespace std;

class UserManager {
	private:
		UserRepository userRepository;
		unordered_map<string, shared_ptr<User> > users;

	public:
		explicit UserManager(const UserRepository &userRepository);

		void addUser(const shared_ptr<User> &user);

		User getUser(const string &name);

		const unordered_map<string, shared_ptr<User> > &getUsers() const;

		void saveUser(const User &user);

		optional<User> loadUser(const string &username);

		vector<User> loadSavedUsers();

		void clearUsers();

};

#endif // USERMANAGER_H