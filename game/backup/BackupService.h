#ifndef IOSERVICE_H
#define IOSERVICE_H

#include "../board/Board.h"
#include "../user/UserManager.h"

class BackupService {
	public:
		void saveBoardToFile(const Board &board, const UserManager &userManager);

		Board loadBoardFromFile(const string &fileName, UserManager &userManager);

		string getBackupFileName() const;
};

#endif
