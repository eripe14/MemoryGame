#ifndef USERGAMESTATS_H
#define USERGAMESTATS_H

class UserGameStats {
	private:
		int pairsFound = 0;
		int mistakes = 0;

	public:
		UserGameStats(int pairsFound, int mistakes);

		int getPairsFound() const;

		int getMistakes() const;

		void addPairFound();

		void addMistake();

		void updateStats(int pairs, int mistakesParameter);
};

#endif //USERGAMESTATS_H
