#ifndef DIFFICULTYPROVIDER_H
#define DIFFICULTYPROVIDER_H
#include "Difficulty.h"

#include <iostream>

using namespace std;

class DifficultyProvider {
	public:
		Difficulty getDifficulty() const {
			int choice = 0;

			cout << "Wybierz poziom trudnosci: " << endl;
			cout << "1. Latwy - karty moga miec tylko jeden znak np. A" << endl;
			cout << "2. Sredni - karty moga miec dwa znaki np. AB" << endl;
			cout << "3. Trudny - karty moga miec trzy znaki np. ABC" << endl;
			cout << "Podaj wybrany poziom trudnosci: ";

			cin >> choice;

			switch (choice) {
				case 1:
					return Difficulty::EASY;
				case 2:
					return Difficulty::MEDIUM;
				case 3:
					return Difficulty::HARD;
				default:
					cout << "Niepoprawny wybor, podaj poziom trudnosci jeszcze raz: " << endl;
					return getDifficulty();
			}
		}
};

#endif