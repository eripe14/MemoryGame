#ifndef SIZEPROVIDER_H
#define SIZEPROVIDER_H

#include <iostream>
#include <utility>

class SizeProvider {
	private:
		SizeProvider() {
		}

		static int getInput(const string &prompt) {
			int value;
			while (true) {
				cout << prompt;
				cin >> value;

				if (cin.fail() || value <= 0) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Prosze wprowadzic poprawna dodatnia liczbe." << endl;
				} else {
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					return value;
				}
			}
		}

		static bool checkSize(const int rows, const int cols) {
			return (rows * cols) % 2 == 0;
		}

	public:
		static pair<int, int> getBoardSize() {
			int rows, cols;

			do {
				rows = getInput("Podaj liczbe wierszy: ");
				cols = getInput("Podaj liczbe kolumn: ");
				if (!checkSize(rows, cols)) {
					cout << "Liczba kolumn i wierszy musi byc parzysta!" <<
						endl;
				}
			} while (!checkSize(rows, cols));

			return make_pair(rows, cols);
		}
};

#endif