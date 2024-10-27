#ifndef MENU_H
#define MENU_H
#include "Game.h"
#include "achievement/AchievementManager.h"
#include "backup/LoadHandler.h"

#include <map>
#include <string>

using namespace std;

class Menu {
	private:
		map<int, string> menuItems;
		shared_ptr<UserManager> userManager;
		shared_ptr<AchievementManager> achievementManager;
		shared_ptr<BackupService> backupService;

	public:
		explicit Menu(UserManager &userManager, AchievementManager &achievementManager, BackupService &backupService)
		: userManager(make_shared<UserManager>(userManager)),
		achievementManager(make_shared<AchievementManager>(achievementManager)),
		backupService(make_shared<BackupService>(backupService)) {
			menuItems[1] = "Nowa gra";
			menuItems[2] = "Wczytaj gre";
			menuItems[3] = "Zobacz statystyki graczy";
			menuItems[4] = "Zobacz osiagniecia";
			menuItems[5] = "Wyjscie";
		}

		void printMenu(LoadHandler &loadHandler, const bool clear, const bool print);
		void handleMenu(LoadHandler &loadHandler);
};

#endif //MENU_H
