#include "main.h"
#ifndef Card_h
#define Card_h

class Card {

public:
	int id;

	//Filler cards only, regular set to null
	char avail_top;
	char avail_bot;
	char avail_right;
	char avail_left;
	//End filler

	char top;				//c = city, r = road, f= field
	char bot;
	char left;
	char right;
	bool isend;				//determines if end of road
	bool iscity;			//determines if tile has a city
	bool isroad;			//determines if tile has road
	bool isfield;			//determines if tile has field
	bool dubpoints;			//determines if tile is worth double points
	bool ismonastery;		//determines if tile is monastery
	char meeplocation;		// t=top, b=bot, l=left, r=right, i=inside

	Card(int x);
	void rotatecw();
};

#endif