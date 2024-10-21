#ifndef CARDTYPESERVICE_H
#define CARDTYPESERVICE_H

#include <string>
#include <vector>
#include <random>
#include "../difficulty/Difficulty.h"

using namespace std;

class CardTypeService {
	private:
		const vector<char> cardTypes = {
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
			'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U',
			'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e',
			'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'x',
			'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', '$',
			'y', 'z', '@',
		};
		mutable mt19937 gen;
		mutable uniform_int_distribution<> dis;

	public:
		CardTypeService() : gen(random_device{}()), dis(0, cardTypes.size() - 1) { }

		string getCardType(const Difficulty difficulty) const {
			int length;
			switch (difficulty) {
				case EASY:
					length = 1;
					break;
				case MEDIUM:
					length = 2;
					break;
				case HARD:
					length = 3;
					break;
				default:
					length = 1;
					break;
			}

			string result;
			result.reserve(length);

			for (int i = 0; i < length; ++i) {
				result += cardTypes[dis(gen)];
			}

			return result;
		}
};

#endif