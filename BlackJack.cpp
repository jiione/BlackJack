#include<iostream>
#include "Game.h"
using namespace std;

int main() {
	Game game;
	int gameNum; //the number of games played
	cout << "Play Game : ";
	cin >> gameNum;
	game.PlayGame(gameNum);
	game.printResult();
}