#include "UserProvider.h"
#include <iostream>
#include <regex>
#include <vector>
#include "UserProvider.h"

using namespace std;

const string ANSI_RESET  = "\033[0m";
const string ANSI_GREEN  = "\033[32m";
const string ANSI_RED  = "\033[31m";

UserProvider::UserProvider(UserManager &userManager) : userManager(userManager) {}

void UserProvider::provideUsers() const {
	const int numberOfPlayers = provideNumberOfPlayers();

	for (int i = 0; i < numberOfPlayers; i++) {
		string playerName;
		cout << "Podaj nazwe gracza " << i + 1 << ": ";
		cin >> playerName;

		if (optional<User> userOptional = userManager.loadUser(playerName); userOptional.has_value()) {
			userManager.addUser(make_shared<User>(userOptional.value()));
			cout << ANSI_GREEN << "Wczytano uzytkownika " << playerName << ANSI_RESET << endl;
			continue;
		}

		const auto player = make_shared<User>(playerName, UserStatistics(playerName));
		userManager.addUser(player);
	}

	if (numberOfPlayers == 1) {
		if (optional<User> userOptional = userManager.loadUser("Komputer"); userOptional.has_value()) {
			userManager.addUser(make_shared<User>(userOptional.value()));
			return;
		}

		const auto computer = make_shared<User>("Komputer", UserStatistics("Komputer"));
		userManager.addUser(computer);
	}
}

int UserProvider::provideNumberOfPlayers() const {
	int numberOfPlayers = 0;
	cout << "Podaj liczbe graczy: ";
	cin >> numberOfPlayers;

	const bool isValidNumber = isValidNumberOfPlayers(to_string(numberOfPlayers));
	if (cin.fail() || !isValidNumber) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << ANSI_RED << "Podana liczba graczy jest nieprawidlowa. Podaj liczbe graczy z zakresu 1-10." << ANSI_RESET << endl;
		return provideNumberOfPlayers();
	}

	return numberOfPlayers;
}

bool UserProvider::isValidNumberOfPlayers(const string &input) const {
	const regex pattern("^(10|[1-9])$");
	return regex_match(input, pattern);
}