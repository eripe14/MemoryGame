#include "Card.h"

using namespace std;

Card::Card() : number(0), cardType(" "), guessed(false) { }

Card::Card(const int number, const string &cardType) : number(number), cardType(cardType), guessed(false) { }

Card::Card(const int number, const string &cardType, const bool guessed) :
	number(number),
	cardType(cardType),
	guessed(guessed) { }

int Card::getNumber() const {
	return number;
}

string Card::getCardType() const {
	return cardType;
}

bool Card::isGuessed() const {
	return guessed;
}

void Card::setGuessed(const bool guessed) {
	this->guessed = guessed;
}