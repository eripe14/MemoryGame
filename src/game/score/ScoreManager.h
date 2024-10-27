#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include "../achievement/AchievementManager.h"
#include "../user/User.h"

#include <memory>
#include <unordered_map>
#include <vector>

using namespace std;

class ScoreManager {
	public:
		explicit ScoreManager(const shared_ptr<AchievementManager> &achievementManager)
			: achievementManager(achievementManager) {}

		void updateScores(const unordered_map<string, shared_ptr<User>>& users);

		void displayFinalScores() const;

	private:
		void updateUserStatistics(const shared_ptr<User> &user, int points, int maxPoints, int minPoints);

		vector<shared_ptr<User>> currentUsers;

		shared_ptr<AchievementManager> achievementManager;
};

#endif