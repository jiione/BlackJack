#pragma once
#include "PlayerWithCC.h"
#include "PlayerWithoutCC.h"
#include "Dealer.h"
#include<iostream>
class Game {
private:
	vector<int> countingTable;
	Decks* decks;
	Dealer* dealer;
	PlayerWithCC* player1;
	PlayerWithoutCC* player2;
	int gameNum;

public:
	Game();
	~Game();
	void PlayGame(int num);
	void Ready(int currentGameNum);
	void printResult();
	void Clear();
};
