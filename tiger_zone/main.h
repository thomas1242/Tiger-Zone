// Putting stuff in here. Can be put in card.h, deck.h etc later.

#include <iostream>
#include <string>
#include <vector>
#include <stack>

#define size 72					//including first card in size

using namespace std;

class Card {

public:
	int id;
	char top;				//c = city, r = road, f= field
	char bot;
	char left;
	char right;
	bool isend;				//determines if end of road
	bool iscity;			//determines if tile has a city
	bool isroad;			//determines if tile has road
	bool isfield;			//determines if tile has field
	bool dubpoints;			//determines if tile is worth double points
	bool ismonastery		//determines if tile is monastery

	card(int x) {
		id = x;
	}

	void rotatecw() {
		char temp = right;
		right = top;
		top = left;
		left = bot;
		bot = temp;
	}



};