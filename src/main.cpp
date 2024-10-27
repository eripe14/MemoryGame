#include "game/Menu.h"
#include "game/backup/BackupService.h"
#include "game/backup/LoadHandler.h"
#include "game/user/UserManager.h"

#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
	BackupService backupService(argv[0]);
	LoadHandler loadHandler = LoadHandler(backupService);
	UserRepository userRepository(make_shared<BackupService>(backupService));
	UserManager userManager(userRepository);
	AchievementManager achievementManager;

	Menu menu = Menu(userManager, achievementManager, backupService);
	menu.printMenu(loadHandler, true, true);

	return 0;
}