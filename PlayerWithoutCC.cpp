#include "PlayerWithoutCC.h"

PlayerWithoutCC::PlayerWithoutCC() {
	this->money = 100000;
	this->win = 0;
	this->betMoney = 0;
}

PlayerWithoutCC::PlayerWithoutCC(int baseBetMoney) {
	this->money = 100000;
	this->win = 0;
	this->betMoney = baseBetMoney;
}

int PlayerWithoutCC::SumOfNum() {
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
void PlayerWithoutCC::ResultGame(string result) {
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

void PlayerWithoutCC::Betting() {
	this->money -= betMoney;
}

bool PlayerWithoutCC::isBlackJack() {
	if (getHands().size() == 2 && SumOfNum() == 21) return true;
	else return false;
}
