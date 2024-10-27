#ifndef IOSERVICE_H
#define IOSERVICE_H

#include "../board/Board.h"
#include "../user/User.h"
#include <filesystem>
#include <unordered_map>

class BackupService {
	private:
		filesystem::path path;

	public:
		BackupService(const char *argv0) {
			path = getExecutablePath(argv0);
		}

		filesystem::path getExecutablePath(const char *argv0) {
			return filesystem::absolute(argv0).parent_path();
		}

		void saveBoardToFile(const shared_ptr<Board> &board, const shared_ptr<User> &currentUser, const unordered_map<string, shared_ptr<User>> &users) const;

		pair<shared_ptr<Board>, string> loadBoardFromFile(const string &fileName) const;

		string getBackupFileName(filesystem::path path) const;

		filesystem::path getFolderPath() const;

		filesystem::path getPath() const {
			return path;
		}

		vector<string> getBackupFiles() const;
};

#endif