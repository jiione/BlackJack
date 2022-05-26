#include "Decks.h"
#include<iostream>
using namespace std;

/*
* Decks class's constructor
* param: (int) Number of decks used when playing games
*/
Decks::Decks(int num) {
	deckNum = num;
	remainCardNum = 52 * num; //Number of total cards
	discardCardNum = 0;
	discardHead = nullptr;
	discardTail = nullptr;
	remainHead = nullptr;
	remainTail = nullptr;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < 4; j++) {
			Card* newCard = new Card(11); //Ace card's value is 11
			if (remainHead == nullptr) {
				remainHead = newCard;
				remainTail = newCard;
			}
			else {
				remainTail->setNext(newCard);
				remainTail = newCard;
			}
			for (int w = 2; w <= 9; w++) {//2~ 9
				newCard = new Card(w);
				remainTail->setNext(newCard);
				remainTail = newCard;
			}
			for (int w = 0; w < 4; w++) { //10, J, Q, K
				newCard = new Card(10);
				remainTail->setNext(newCard);
				remainTail = newCard;
			}
		}
	}
}


/*Shuffle the deck.
* The most common shuffle is implemented in code.
*/
void Decks::Shuffle() {
	if (discardCardNum != 0) {
		remainTail->setNext(discardHead);
		remainTail = discardTail;
		remainTail->setNext(nullptr);
	}

	discardHead = nullptr;
	discardTail = nullptr;

	remainCardNum = deckNum * 52;


	srand(time(NULL));

	for (int i = 0; i < 100; i++) { //Repeat 100 times to mix thoroughly
		Card* currCard = remainHead;
		Card* prevCard = remainHead;
		int count;

		/*Step1: Divide a bunch of cards from the deck*/
		for (count= 0; count < rand() % remainCardNum; count++) {
			prevCard = currCard;
			currCard = currCard->getNext();
		}
		discardCardNum = remainCardNum - count;
		remainCardNum = count;
		if (remainCardNum == 0) {
			discardHead = remainHead;
			discardTail = remainTail;
			discardTail->setNext(nullptr);
			remainHead = nullptr;
			remainTail = nullptr;
		}
		else {
			discardHead = currCard;
			discardTail = remainTail;
			remainTail = prevCard;
			remainTail->setNext(nullptr);
		}
		/*Step2: Randomly put it on the deck from a bunch of cards divided.*/
		while (discardCardNum != 0) {
			currCard = discardHead;
			for (count = 0; count < rand() % discardCardNum; count++) {
				currCard = currCard->getNext();
			}
			discardCardNum = discardCardNum - (count + 1);
			remainCardNum = remainCardNum + (count + 1);
			Card* tmpCard = currCard->getNext();
			currCard->setNext(remainHead);
			if (remainTail == nullptr) {
				remainTail = currCard;
			}
			remainHead = discardHead;
			discardHead = tmpCard;
		}
		discardTail = nullptr;
	}
}

/*Give the card at the top of the deck*/
Card* Decks::Dealing() {
	if (remainCardNum == 0) {
		return nullptr;
	}
	Card* DealingCard = remainHead;
	remainHead = remainHead->getNext();
	remainCardNum--;
	if (discardCardNum == 0) {
		discardHead = discardTail = DealingCard;
	}
	else {
		discardTail->setNext(DealingCard);
		discardTail = DealingCard;
	}
	discardCardNum++;
	return DealingCard;
}

/*If there is 20% left on the card, shuffle the deck*/
bool Decks::isShuffle() {
	return remainCardNum / (double)(remainCardNum + discardCardNum) < 0.2;
}