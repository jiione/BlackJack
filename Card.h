#pragma once

class Card {
private:
	int value;
	Card* next;
public:
	Card() { this->value = 0; this->next = nullptr; }
	Card(int v) { this->value = v; this->next = nullptr; }

	/*getter & setter*/
	int getValue() { return this->value; }
	Card* getNext() { return this->next; }
	void setValue(int v) { this->value = v; }
	void setNext(Card* p) { this->next = p; }
};
