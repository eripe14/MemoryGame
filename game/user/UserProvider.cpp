#include "UserProvider.h"
#include <iostream>
#include <regex>
#include <vector>
#include "UserProvider.h"

using namespace std;

UserProvider::UserProvider(UserManager &userManager) : userManager(userManager) {}

void UserProvider::provideUsers() const {
	const int numberOfPlayers = provideNumberOfPlayers();

	for (int i = 0; i < numberOfPlayers; i++) {
		string playerName;
		cout << "Podaj nazwe gracza " << i + 1 << ": ";
		cin >> playerName;

		const auto player = make_shared<User>(playerName);
		userManager.addUser(player);
	}

	if (numberOfPlayers == 1) {
		const auto computer = make_shared<User>("Komputer");
		userManager.addUser(computer);
	}
}

int UserProvider::provideNumberOfPlayers() const {
	int numberOfPlayers = 0;
	cout << "Podaj liczbe graczy: ";
	cin >> numberOfPlayers;

	const bool isValidNumber = isValidNumberOfPlayers(to_string(numberOfPlayers));
	if (!isValidNumber) {
		cout << "Podana liczba graczy jest nieprawidlowa. Podaj liczbe graczy z zakresu 1-10." << endl;
		return provideNumberOfPlayers();
	}

	return numberOfPlayers;
}

bool UserProvider::isValidNumberOfPlayers(const string &input) const {
	regex pattern("^[1-9]$");
	return regex_match(input, pattern);
}