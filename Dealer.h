#pragma once
#include"Human.h"
class Dealer : public Human {
public:
	int SumOfNum() {
		int sum = 0;
		for (auto it : getHands()) {
			sum += it->getValue();
		}
		return sum;
	}
	bool HitStatus() {
		return SumOfNum() < 17;
	}
	bool isBlackJack() {
		if (getHands().size() == 2 && SumOfNum() == 21) return true;
		else return false;
	}
};
