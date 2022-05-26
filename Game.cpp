#include "Game.h"

Game::Game(){
	countingTable.resize(12, 0);
	gameNum = 0;
	decks = new Decks(3);
	dealer = new Dealer;
	player1 = new PlayerWithCC(500);
	player2 = new PlayerWithoutCC(500);
	decks->Shuffle();
}

Game::~Game() {
	delete decks;
	delete dealer;
	delete player1;
	delete player2;
}

void Game::PlayGame(int num) {
	int win = 0;
	int lose = 0;
	gameNum = num; ////the number of games played
	for (int i = 0; i < num; i++) {
		/*Step 1: Bet and hand out cards*/
		Ready(i);
		Card* dealingCard;
	
		/*Step 2: Player 1's turn*/
		while (player1->SumOfNum() < 21 && player1->HitStatus(dealer->getHands(),countingTable,decks)) {
			/*Player1 Hit*/
			dealingCard = decks->Dealing();
			player1->addCard(dealingCard);
			countingTable[dealingCard->getValue()]++;
		}
		/*Player 1 Stand or Bust*/

		/*Step3: Player 2 turn*/
		while (player2->SumOfNum() < 21 &&  player2->HitStatus()) {
			/*Player 2 Hit*/
			dealingCard = decks->Dealing();
			player2->addCard(dealingCard);
			countingTable[dealingCard->getValue()]++;
		}
		/*Player 2 Stand or Bust*/
		
		/*Step4: Dealer turn*/
		countingTable[dealer->getHands().front()->getValue()]++;
		while (dealer->SumOfNum() < 21 && dealer->HitStatus() ) {
			/*Dealer Hit*/
			dealingCard = decks->Dealing();
			dealer->addCard(dealingCard);
			countingTable[dealingCard->getValue()]++;
		}
		/*Dealer Stand or Bust*/

		/*Step5: Check the results*/
		/*Player 1's result*/
		if (player1->SumOfNum() > 21) { //If Player 1 Bust
			player1->ResultGame("LOSE");
		}
		else if (dealer->SumOfNum() > 21) {//If Dealer Bust
			player1->ResultGame("WIN");
		}
		else if (player1->isBlackJack() && !dealer->isBlackJack()) {//Player 1 is BlackJack!! and Dealer is not BlackJack
			player1->ResultGame("BLACKJACK");
		}
		else if (dealer->SumOfNum() > player1->SumOfNum()) {//Dealer's cards are higher
			player1->ResultGame("LOSE");
		}
		else if (dealer->SumOfNum() < player1->SumOfNum()) {//Player1's cards are higher
			player1->ResultGame("WIN");
		}
		
		else {
			player1->ResultGame("DRAW"); //Player1's cards = Dealer's cards
		}

		/*Player 2's result*/
		if (player2->SumOfNum() > 21) {
			player2->ResultGame("LOSE");
		}
		else if (dealer->SumOfNum() > 21) {
			player2->ResultGame("WIN");
		}
		else if (player2->isBlackJack() && !dealer->isBlackJack()) {
			player2->ResultGame("BLACKJACK");
		}
		else if (dealer->SumOfNum() > player2->SumOfNum()) {
			player2->ResultGame("LOSE");
		}
		else if (dealer->SumOfNum() < player2->SumOfNum()) {
			player2->ResultGame("WIN");
		}
		else {
			player2->ResultGame("DRAW");
		}

		/*Step 6: If there is 20% left on the card, shuffle the deck*/
		if (decks->isShuffle()) { 
			decks->Shuffle();

			/*Initialize counting Table*/
			countingTable.clear();
			countingTable.resize(12,0);
		}

		/*Step 7: Initialize hands of Dealer and Players */
		Clear();
	}
}

/*Players bet and hand out two cards to players*/
void Game::Ready(int currentGameNum) {
	double winningRate = player1->getWin() / (double)currentGameNum;
	if (winningRate< 0.40) player1->setBetMoney(500);
	else if (winningRate < 0.44) player1->setBetMoney(300);
	else player1->setBetMoney(100);
	player1->Betting();
	player2->Betting();
	Card* dealingCard = decks->Dealing();
	dealer->addCard(dealingCard);
	dealingCard = decks->Dealing();
	dealer->addCard(dealingCard);
	countingTable[dealingCard->getValue()]++;

	dealingCard = decks->Dealing();
	player1->addCard(dealingCard);
	countingTable[dealingCard->getValue()]++;

	dealingCard = decks->Dealing();
	player1->addCard(dealingCard);
	countingTable[dealingCard->getValue()]++;

	dealingCard = decks->Dealing();
	player2->addCard(dealingCard);
	countingTable[dealingCard->getValue()]++;

	dealingCard = decks->Dealing();
	player2->addCard(dealingCard);
	countingTable[dealingCard->getValue()]++;
}

/*Output game results on screen*/
void Game::printResult() {
	cout << "<< Player1 >>" << endl;
	cout << "½Â¸® : " << player1->getWin() << " ¹«½ÂºÎ ¹× ÆÐ¹è : " << gameNum - player1->getWin() << endl;
	cout << "½Â·ü: " << player1->getWin() / (double)gameNum * 100 <<"%" << endl;
	cout << "money : " << player1->getMoney() << endl<<endl;

	cout << "<< Player2 >>" << endl;
	cout << "½Â¸® : " << player2->getWin() << " ¹«½ÂºÎ ¹× ÆÐ¹è : " << gameNum - player2->getWin() << endl;
	cout << "½Â·ü: " << player2->getWin() / (double)gameNum * 100 << "%" << endl;
	cout << "money : " << player2->getMoney() << endl;
}

void Game::Clear() {
	dealer->Clear();
	player1->Clear();
	player2->Clear();
}

