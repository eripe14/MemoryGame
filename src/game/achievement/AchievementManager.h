#ifndef ACHIEVEMENTMANAGER_H
#define ACHIEVEMENTMANAGER_H
#include "Achievement.h"
#include "../user/User.h"

#include <iostream>
#include <map>
#include <memory>
#include <string>

using namespace std;

const string ANSI_RESET = "\033[0m";
const string ANSI_GREEN = "\033[32m";
const string ANSI_BOLD_YELLOW = "\e[1;33m";
const string ANSI_RED = "\033[31m";
const string ANSI_GRAY = "\033[38m";

class AchievementManager {
	private:
		map<string, shared_ptr<Achievement> > achievements;

	public:
		AchievementManager() {
			achievements["firstWin"] = make_shared<Achievement>(
				"Pierwsze zwyciestwo",
				"Wygraj swoja pierwsza gre"
				);

			achievements["perfectGame"] = make_shared<Achievement>(
				"Bezbledna gra",
				"Wygraj gre nie popelniajac zadnego bledu"
				);

			achievements["persistentPlayer"] = make_shared<Achievement>(
				"Wytrwaly gracz",
				"Zagraj 10 gier"
				);

			achievements["computerBeater"] = make_shared<Achievement>(
				"Pogromca AI",
				"Wygraj z komputerem"
				);
		}

		void printAchievements() {
			int i = 1;
			for (const auto &pair : achievements) {
				cout << i << ". " << pair.second->getName() << endl << pair.second->getDescription() << endl;
				cout << ANSI_GRAY << "-------------------" << ANSI_RESET << endl;
				i++;
			}
			cout << endl << endl;
		}

		void unlockAchievement(const string &name, const shared_ptr<User> &user) {
			const auto achievementIt = achievements.find(name);
			if (achievementIt == achievements.end() || !achievementIt->second) {
				return;
			}

			user->unlockAchievement(*achievementIt->second);

			cout << ANSI_GRAY << "--- " << ANSI_BOLD_YELLOW << "Osiagniecie" << ANSI_GRAY << " ---" << ANSI_RESET << endl;
			cout << "Gracz " << ANSI_GREEN << user->getName() << ANSI_RESET << " zdobyl osiagniecie: " << achievementIt->second->getName() << endl;
			cout << ANSI_GRAY << "-------------------" << ANSI_GRAY << endl << endl;
		}
};

#endif //ACHIEVEMENTMANAGER_H