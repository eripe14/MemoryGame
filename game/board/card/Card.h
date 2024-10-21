#ifndef CARD_H
#define CARD_H
#include <string>

using namespace std;

class Card {
	private:
		int number;
		string cardType;
		bool guessed;

	public:
		Card();

		Card(const int number, const string &cardType);

		Card(const int number, const string &cardType, const bool guessed);

		int getNumber() const;

		string getCardType() const;

		bool isGuessed() const;

		void setGuessed(const bool guessed);
};

#endif