#include "main.h"
#include "card.h"

Card::card(int x, char top, char bot, char left, char right) {
	id = x;
	avail_top = 0;
	avail_bot = 0;
	avail_right = 0;
	avail_left = 0;
}

void Card::rotatecw() {
	char temp = right;
	right = top;
	top = left;
	left = bot;
	bot = temp;
}