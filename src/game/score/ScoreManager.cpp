#include "ScoreManager.h"

#include <iostream>
#include <limits>

void ScoreManager::updateScores(const unordered_map<string, shared_ptr<User>>& users) {
	for (auto pair : users) {
		currentUsers.push_back(pair.second);
	}

    int maxPoints = numeric_limits<int>::min();
    int minPoints = numeric_limits<int>::max();

    for (const auto& pair : users) {
    	const shared_ptr<User> user = pair.second;
        int points = user->getPoints();

        maxPoints = max(maxPoints, points);
        minPoints = min(minPoints, points);
    }

    for (const auto& pair : users) {
    	const shared_ptr<User> user = pair.second;
        updateUserStatistics(user, user->getPoints(), maxPoints, minPoints);
    }
}

void ScoreManager::displayFinalScores() const {
    system("cls");
    cout << R"(
         _____     _          _                              _ _     __
        |_   _|_ _| |__   ___| | __ _  __      ___   _ _ __ (_) | __/_/__      __
          | |/ _` | '_ \ / _ \ |/ _` | \ \ /\ / / | | | '_ \| | |/ / _ \ \ /\ / /
          | | (_| | |_) |  __/ | (_| |  \ V  V /| |_| | | | | |   < (_) \ V  V /
          |_|\__,_|_.__/ \___|_|\__,_|   \_/\_/  \__, |_| |_|_|_|\_\___/ \_/\_/
                                             |___/
    )";
    cout << endl;
    cout << endl;

    int maxPairsFound = numeric_limits<int>::min();
    vector<shared_ptr<User>> winners;
    vector<pair<shared_ptr<User>, string>> unlockedAchievements;

    for (const auto& user : currentUsers) {
        const auto& stats = user->getStatistics();
        UserGameStats gameStats = user->getGameStats();

        cout << "Gracz: " << ANSI_GREEN << user->getName() << ANSI_RESET;
        cout << " - Punkty: " << ANSI_BOLD_YELLOW << user->getPoints() << ANSI_RESET << endl;
        cout << "Znalezione pary: " << gameStats.getPairsFound() << endl;
        cout << "Bledy: " << gameStats.getMistakes() << endl;

        cout << "Wygrane: " << stats.getGameWon() << endl;
        cout << "Przegrane: " << stats.getGameLost() << endl;
        cout << "Remisy: " << stats.getGameDraw() << endl;
        cout << "-------------------" << endl;

        if (user->getStatistics().getGameWon() == 1 && !user->hasAchievement("Pierwsze zwyciestwo")) {
            unlockedAchievements.push_back({user, "firstWin"});
        }

        if (user->getGamePlayed() == 10 && !user->hasAchievement("Wytrwaly gracz")) {
            unlockedAchievements.push_back({user, "persistentPlayer"});
        }

        if (gameStats.getPairsFound() > maxPairsFound) {
            maxPairsFound = gameStats.getPairsFound();
            winners.clear();
            winners.push_back(user);
        } else if (gameStats.getPairsFound() == maxPairsFound) {
            winners.push_back(user);
        }
    }

    cout << endl;

    if (winners.size() == 1) {
        auto winner = winners[0];
        cout << "Gracz " << winner->getName() << " wygral gre z " << maxPairsFound << " znalezionymi parami!" << endl << endl;

        if (winner->getGameStats().getMistakes() == 0 && !winner->hasAchievement("Bezbledna gra")) {
            unlockedAchievements.push_back({winner, "perfectGame"});
        }

        bool playedWithComputer = false;
        for (const auto& user : currentUsers) {
            if (user->getName() == "Komputer") {
                playedWithComputer = true;
                break;
            }
        }

        if (playedWithComputer && winner->getName() != "Komputer" && !winner->hasAchievement("Pogromca AI")) {
            unlockedAchievements.push_back({winner, "computerBeater"});
        }
    } else {
        cout << "Remis pomiedzy: ";
        for (const auto& winner : winners) {
            cout << winner->getName() << " ";
        }
        cout << "z " << maxPairsFound << " znalezionymi parami!" << endl;
    }

    for (const auto& [user, achievementName] : unlockedAchievements) {
        achievementManager->unlockAchievement(achievementName, user);
    }
}

void ScoreManager::updateUserStatistics(const shared_ptr<User> &user, const int points, const int maxPoints, const int minPoints) {
    UserStatistics stats = user->getStatistics();

    if (points == maxPoints && maxPoints != minPoints) {
        stats.addGameWon();
    } else if (points == minPoints && maxPoints != minPoints) {
    	stats.addGameLost();
    } else {
        stats.addGameDraw();
    }

    user->setStatistics(stats);
}