#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H
#include <string>

using namespace std;

class Achievement {
	private:
		string name;
		string description;
	public:
		Achievement() = default;
		Achievement(const string &name, const string &description) : name(name), description(description) {};

		string getName() const {
			return name;
		};

		string getDescription() const {
			return description;
		};
};

#endif //ACHIEVEMENT_H
