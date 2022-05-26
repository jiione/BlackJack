#pragma once
#include"Human.h"
class PlayerWithCC : public Human {
private:
	int money;
	int win;
	int betMoney;
public:
	PlayerWithCC();
	PlayerWithCC(int baseBetMoney);
	
	/*getter & setter*/
	int getMoney() { return this->money; }
	int getWin() { return this->win; }

	void setBetMoney(int money) { this->betMoney = money; }
	
	void Betting();
	int SumOfNum();
	void ResultGame(string result);
	bool HitStatus(vector<Card*> dealerHands, vector<int> countingTable, Decks* decks);
	bool isBlackJack();
};
