#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <memory>
#include <unordered_map>
#include <string>
#include "User.h"

using namespace std;

class UserManager {
private:
    unordered_map<string, shared_ptr<User>> users;

public:
    void addUser(const shared_ptr<User> &user);

    User getUser(const string &name);

	const unordered_map<string, shared_ptr<User>>& getUsers() const;
};

#endif // USERMANAGER_H