#pragma once
#include "Decks.h"
#include<algorithm>
#include<string>
#include <vector>

using namespace std;

class Human {
private:
	vector<Card*> hands;
public:
	Human(){}
	/*getter & setter*/
	vector<Card*> getHands() { return this->hands; }

	void addCard(Card* card) { hands.push_back(card); }
	void Clear() { hands.clear(); }

	virtual int SumOfNum() = 0; //The sum of the card values in the hand
	virtual bool isBlackJack() = 0;//Check Blackjack
};
