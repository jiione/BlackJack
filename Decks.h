#pragma once
#include "Card.h"
#include <time.h>
#include <stdlib.h>
class Decks {
private:
	int deckNum;

	/*remaining deck*/
	Card* remainHead;
	Card* remainTail;
	int remainCardNum;

	/*discarded deck*/
	Card* discardHead;
	Card* discardTail;
	int discardCardNum;
public:
	/*constructors*/
	Decks() {}
	Decks(int num);

	/*getter & setter*/
	int getDeckNum() { return this->deckNum; }
	Card* getRemainHead() { return this->remainHead; }
	Card* getRemainTail() { return this->remainTail; }
	int getRemainCardNum() { return this->remainCardNum; }
	Card* getDiscardHead() { return this->discardHead; }
	Card* getDiscardTail() { return this->discardTail; }
	int getDiscardCardNum() { return this->discardCardNum; }

	void setDeckNum(int num) { this->deckNum = num; }
	void setRemainHead(Card* ptr) { this->remainHead = ptr; }
	void setRemainTail(Card* ptr) { this->remainTail = ptr; }
	void setRemainCardNum(int num) { this->remainCardNum = num; }
	void setDiscardHead(Card* ptr) { this->discardHead = ptr; }
	void setDiscardTail(Card* ptr) { this->discardTail = ptr; }
	void setDiscardCardNum(int num) { this->discardCardNum = num; }

	void Shuffle();
	Card* Dealing();
	bool isShuffle();
};