#include "LoadHandler.h"
#include <iostream>
#include <limits>

using namespace std;

LoadHandler::LoadHandler(BackupService &backupService) : backupService(backupService) { }

string formatFileName(string fileName) {
	if (fileName.empty()) {
		return fileName;
	}

	constexpr size_t expectedExtLength = 5;
	if (fileName.length() <= expectedExtLength) {
		return fileName;
	}

	string result = fileName;
	int underscoreCount = 0;

	for (char& c : result) {
		if (c == '_') {
			c = (underscoreCount < 3) ? '/' : (underscoreCount < 6) ? ':' : '_';
			++underscoreCount;
		}
	}

	return result.substr(0, result.length() - expectedExtLength);
}

string LoadHandler::chooseBackup() const {
	vector<string> backupFiles = backupService.getBackupFiles();
	map<int, string> backupFilesMap;
	for (int i = 0; i < backupFiles.size(); i++) {
		backupFilesMap.insert({i + 1, backupFiles[i]});
	}

	int choice = 0;

	while (true) {
		for (const auto& pair : backupFilesMap) {
			string formattedDate = formatFileName(pair.second);
			cout << "\033[1;33m" << pair.first << ". " << "\033[0;37m" << formattedDate << "\033[0m" << endl;
		}

		cout << "Wybierz plik do wczytania: ";
		cin >> choice;

		if (cin.fail() || backupFilesMap.find(choice) == backupFilesMap.end()) {
			cout << ANSI_RED << "Nieprawidlowy wybor, sprobuj ponownie." << ANSI_RESET << endl;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} else {
			break;
		}
	}

	return backupFilesMap[choice];
}

pair<string, Game> LoadHandler::loadGame(UserManager &userManager) const {
	const string selectedFile = chooseBackup();
	const auto board = backupService.loadBoardFromFile(selectedFile);
	Game game(
		make_shared<UserManager>(userManager),
		board.first,
		make_shared<BackupService>(backupService),
		make_shared<BoardManager>(),
		make_shared<AchievementManager>()
	);

	return pair<string, Game>(board.second, game);
};


bool LoadHandler::wantsToLoad() const {
	system("cls");
	char input;

	cout << "Czy chcesz wczytac gre? (t/n): ";
	cin >> input;

	if (input == 't') {
		vector<string> backupFiles = backupService.getBackupFiles();

		if (backupFiles.empty()) {
			cout << ANSI_RED << "Brak zapisanych gier." << ANSI_RESET << endl;
			return false;
		}

		return true;
	}

	return false;
}