#ifndef LOADHANDLER_H
#define LOADHANDLER_H
#include "BackupService.h"
#include "../Game.h"

class LoadHandler {
	private:
		BackupService &backupService;

	public:
		LoadHandler(BackupService &backupService);

		string chooseBackup() const;

		pair<string, Game> loadGame(UserManager &userManager) const;

		bool wantsToLoad() const;

};

#endif //LOADHANDLER_H
