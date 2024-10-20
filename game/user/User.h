#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
private:
    const string name;
    int points;

public:
    User(const string &name);

	User(const string &name, const int points);

    string getName() const;

    int getPoints() const;

    void addPoints(const int points);
};

#endif
