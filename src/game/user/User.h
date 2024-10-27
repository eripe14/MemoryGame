#ifndef USER_H
#define USER_H

#include "UserGameStats.h"
#include "UserStatistics.h"
#include "../achievement/Achievement.h"

#include <map>
#include <string>
#include <unordered_map>
using namespace std;

class User {
	private:
		const string name;
		UserStatistics statistics;
		UserGameStats gameStats;
		int points;
		unordered_map<string, Achievement> unlockedAchievements;

	public:
		User(const string &name, const UserStatistics &statistics);

		User(const string &name, const UserStatistics &statistics, const int points);

		User(
			const string &name,
			const UserStatistics &statistics,
			const UserGameStats &gameStats,
			const int points
			);

		string getName() const;

		UserStatistics getStatistics() const;

		void setStatistics(const UserStatistics &other);

		int getPoints() const;

		void addPoints(const int points);

		UserGameStats getGameStats() const;

		void setGameStats(const UserGameStats &stats);

		void unlockAchievement(const Achievement &achievement);

		void printAchievements() const;

		int getGamePlayed() const;

		bool hasAchievement(const string &name) const;

		unordered_map<string, Achievement> getUnlockedAchievements() const;
};

#endif