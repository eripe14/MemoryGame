#include "Menu.h"

#include "board/SizeProvider.h"
#include "board/difficulty/DifficultyProvider.h"
#include "user/UserProvider.h"

using namespace std;

// Napis został wygenerowany za pomocą strony: https://www.asciiart.eu/text-to-ascii-art
void printLogo() {
	cout << ANSI_GRAY << R"(
		    _____                                                                         _____
		   ( ___ )-----------------------------------------------------------------------( ___ )
		    |   |                                                                         |   |
		    |   |                                                                         |   |
		    |   |                                                                         |   |
		    |   |    __  __                                  ____                         |   |
		    |   |   |  \/  | ___ _ __ ___   ___  _ __ _   _ / ___| __ _ _ __ ___   ___    |   |
		    |   |   | |\/| |/ _ \ '_ ` _ \ / _ \| '__| | | | |  _ / _` | '_ ` _ \ / _ \   |   |
		    |   |   | |  | |  __/ | | | | | (_) | |  | |_| | |_| | (_| | | | | | |  __/   |   |
		    |   |   |_| _|_|\___|_| |_| |_|\___/|_|   \__, |\____|\__,_|_| |_| |_|\___|   |   |
		    |   |   | |/ /__ _ _ __ ___ | | |  _ \ _ _|___/  _ __ (_) __ _                |   |
		    |   |   | ' // _` | '__/ _ \| | | | | | '__/ _ \| '_ \| |/ _` |               |   |
		    |   |   | . \ (_| | | | (_) | | | |_| | | | (_) | | | | | (_| |               |   |
		    |   |   |_|\_\__,_|_|  \___/|_| |____/|_|  \___/|_| |_|_|\__,_|               |   |
		    |   |                                                                         |   |
		    |   |                                                                         |   |
		    |___|                                                                         |___|
		   (_____)-----------------------------------------------------------------------(_____)

	)" << ANSI_RESET << endl << endl << endl;
}

void Menu::printMenu(LoadHandler &loadHandler, const bool clear, const bool print) {
	if (clear) {
		system("cls");
	}

	if (print) {
		printLogo();
	}

	for (const auto &pair : menuItems) {
		cout << pair.first << ". " << pair.second << endl;
	}

	handleMenu(loadHandler);
}

void Menu::handleMenu(LoadHandler &loadHandler) {
    while (true) {
        int choice = 0;
        cout << "Wybierz opcje: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ANSI_RED << "Niepoprawny wybor." << ANSI_RESET << endl;
            continue;
        }

        const UserProvider userProvider(*userManager);
        const DifficultyProvider difficultyProvider;
        const CardTypeService cardTypeService;

        Difficulty difficulty;
        pair<int, int> boardSize;
        shared_ptr<Board> board;
        vector<User> users;

        switch (choice) {
            case 1: {
            	system("cls");
            	printLogo();

                userProvider.provideUsers();
                difficulty = difficultyProvider.getDifficulty();
                boardSize = SizeProvider::getBoardSize();

                board = make_shared<Board>(boardSize.first, boardSize.second, difficulty);
                if (!board) {
                    cerr << "Nie udalo sie stworzyc planszy." << endl;
                    cout << "\nNacisnij Enter, aby kontynuowac...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                    return;
                }

                board->createCards(cardTypeService, difficulty);

                Game game(
                    userManager,
                    board,
                    backupService,
                    make_shared<BoardManager>(),
                    achievementManager
                );

                game.startGame(nullopt);

            	cout << ANSI_GREEN << "\nNacisnij Enter, aby wrocic do menu..." << ANSI_RESET;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                printMenu(loadHandler, true, true);
                break;
            }
            case 2: {
                if (loadHandler.wantsToLoad()) {
                    auto loadedGame = loadHandler.loadGame(*userManager);
                    loadedGame.second.startGame(optional<string>(loadedGame.first));
                }

            	cout << ANSI_GREEN << "\nNacisnij Enter, aby wrocic do menu..." << ANSI_RESET;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                printMenu(loadHandler, true, true);
                break;
            }
            case 3: {
                users = userManager->loadSavedUsers();
                system("cls");

            	if (users.empty()) {
            		cout << ANSI_RED << "Brak zapisanych graczy." << ANSI_RESET << endl;
            	}

                for (const User &user : users) {
                    cout << "Gracz: " << ANSI_GREEN << user.getName() << ANSI_RESET << endl;
                    cout << "Wygrane: " << user.getStatistics().getGameWon() << endl;
                    cout << "Przegrane: " << user.getStatistics().getGameLost() << endl;
                    cout << "Remisy: " << user.getStatistics().getGameDraw() << endl;
                	user.printAchievements();
                }

            	cout << ANSI_GREEN << "\nNacisnij Enter, aby wrocic do menu..." << ANSI_RESET;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                printMenu(loadHandler, false, false);
                break;
            }
            case 4: {
                system("cls");
                achievementManager->printAchievements();

            	cout << ANSI_GREEN << "\nNacisnij Enter, aby wrocic do menu..." << ANSI_RESET;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                printMenu(loadHandler, false, false);
                break;
            }
            case 5: {
            	exit(0);
            }
            default: {
                cout << ANSI_RED << "Niepoprawny wybor." << ANSI_RESET << endl;
                cout << "\nNacisnij Enter, aby kontynuowac...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                continue;
            }
        }
    }
}