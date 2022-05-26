#include "PlayerWithCC.h"
#include<iostream>

PlayerWithCC::PlayerWithCC() {
	this->money = 100000;
	this->win = 0;
	this->betMoney = 0;
}

PlayerWithCC::PlayerWithCC(int baseBetMoney) {
	this->money = 100000;
	this->win = 0;
	this->betMoney = baseBetMoney;
}

/*Determine the Hit or Stand*/
bool PlayerWithCC::HitStatus(vector<Card*> dealerHands, vector<int> countingTable, Decks* decks) {
	int max = 0;
	int presumption = 0;
	int presumptionSum = 0;
	int bustNum = 0;
	int sum = 0;
	int count = 0;
	double prob = 0;

	/*Step1: Predict the dealer's card.*/
	for (int i = 2; i <= 11; i++) {
		if (i == 10) {
			if (max < 4 * 4 * decks->getDeckNum() - countingTable[i]) {
				max = 4 * 4 * decks->getDeckNum() - countingTable[i];
				presumption = i;
			}
		}
		else {
			if (max < 4 * decks->getDeckNum() - countingTable[i]) {
				max = 4 * decks->getDeckNum() - countingTable[i];
				presumption = i;
			}
		}
	}

	/*Step2: Assume the dealer's card as the predicted value and calculate the Bust probability*/
	presumptionSum = presumption + dealerHands[1]->getValue();
	if (presumptionSum < 17) {
		bustNum = 22 - presumptionSum;	
		for (int i = bustNum; i <= 11; i++) {
			count += countingTable[i];
		}
		if (bustNum == 11) {
			prob = (4 * decks->getDeckNum() - count) / (double)decks->getRemainCardNum();
		}
		else if (bustNum < 11) {
			for (int i = bustNum; i < 10; i++) {
				sum += 4 * decks->getDeckNum();
			}
			sum += 4 * 4 * decks->getDeckNum();
			prob = (sum - count) / (double)decks->getRemainCardNum();
		}
		else {
			prob = 0;
		}

		/*Step3: Stand if dealer have a high probability of bust*/
		if (prob > 0.7) return false;
	}

	/*
	* Step4: Find the probability that the player will bust.
	* and Find the probability of beating the dealer.
	*/
	bustNum = 22 - SumOfNum();
	int minNum = 0;
	int minCount = 0;
	double minProb = 0;
	sum = 0;
	count = 0;

	/*Estimate the sum of dealer if dealer hit*/
	if (presumptionSum<17) {
		for (int i = 2; i <= 11; i++) {
			if (i == 10) {
				if (max < 4 * 4 * decks->getDeckNum() - countingTable[i]) {
					max = 4 * 4 * decks->getDeckNum() - countingTable[i];
					presumption = i;
				}
			}
			else {
				if (max < 4 * decks->getDeckNum() - countingTable[i]) {
					max = 4 * decks->getDeckNum() - countingTable[i];
					presumption = i;
				}
			}
		}
		presumptionSum += presumption;
	}

	/*Find the probability that the player will beat the dealer*/
	if (presumptionSum < 22 && presumptionSum>SumOfNum()) {
		minNum = presumptionSum - SumOfNum() + 1;
		for (int i = minNum ; i < bustNum; i++) {
			if (i == 10) minCount += 4 * 4 * decks->getDeckNum() - countingTable[i];
			else if (i <= 11) minCount += 4 * decks->getDeckNum() - countingTable[i];
		}
	}
	minProb = (double)minCount / decks->getRemainCardNum();
	for (int i = bustNum; i <= 10; i++) {
		count += countingTable[i];
	}
	if (bustNum < 11) {
		for (int i = bustNum; i < 10; i++) {
			sum += 4 * decks->getDeckNum();
		}
		sum += 4 * 4 * decks->getDeckNum();
		prob = (sum - count) / (double)decks->getRemainCardNum();
	}
	else {
		prob = 0;
	}

	/*Step5: Stand if player have a high probability of bust*/
	if (minProb > 0.7)return true;
	else if (prob > 0.4) return false;

	/*Step6: If it's not all, hit*/
	return true;
}

void PlayerWithCC::Betting() {
	this->money -= betMoney;
}

int PlayerWithCC::SumOfNum() {
	int sum = 0;
	vector<Card*> v = getHands();
	sort(v.begin(), v.end());
	for (auto it : v) {
		sum += it->getValue();
		if (it->getValue() == 11 && sum > 21) sum -= 10;
	}
	return sum;
}

/*Apply game results*/
void PlayerWithCC::ResultGame(string result) {
	if (result.compare("WIN") == 0) {
		this->money += betMoney * 2;
		win++;
	}
	else if (result.compare("DRAW") == 0) {
		this->money += betMoney;
	}
	else if (result.compare("LOSE") == 0) {
	}
	else if (result.compare("BLACKJACK") == 0) {
		this->money += betMoney * 2 + betMoney / 2;
		win++;
	}
}

bool PlayerWithCC::isBlackJack() {
	if (getHands().size() == 2 && SumOfNum() == 21) return true;
	else return false;
}
