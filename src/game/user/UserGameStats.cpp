#include "UserGameStats.h"

UserGameStats::UserGameStats(int pairsFound, int mistakes)
: pairsFound(pairsFound), mistakes(mistakes) {}

int UserGameStats::getPairsFound() const {
	return pairsFound;
}

int UserGameStats::getMistakes() const {
	return mistakes;
}

void UserGameStats::addPairFound() {
	pairsFound++;
}

void UserGameStats::addMistake() {
	mistakes++;
}

void UserGameStats::updateStats(const int pairs, const int mistakesParameter) {
	pairsFound       = pairs;
	mistakes         = mistakesParameter;
}