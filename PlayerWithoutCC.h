#pragma once
#include"Human.h"

class PlayerWithoutCC : public Human {
private:
	int money;
	int win;
	int betMoney;

public:
	PlayerWithoutCC();
	PlayerWithoutCC(int baseBetMoney);

	/*getter & setter*/
	int getMoney() { return this->money; }
	int getWin() { return this->win; }

	void Betting();
	int SumOfNum();
	bool HitStatus() {
		return SumOfNum() < 17;
	}
	bool isBlackJack();
	void ResultGame(string result);
};
