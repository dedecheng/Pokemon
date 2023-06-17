/***********************************************************************
 * File: Variable.cpp
 * Author: Raymin (B11132009)
 * Create Date: 2023--06-14
 * Editor: Raymin (B11132009)
 * Update Date: 2023--06-14
 * Description: variable and operator for game
***********************************************************************/

#include "Variable.h"

// operator + for position
Position operator + (const Position& a, const Position& b) {
	return Position{ a.x + b.x, a.y + b.y };
}

// operator - for position
Position operator - (const Position& a, const Position& b) {
	return Position{ a.x - b.x, a.y - b.y };
}

// operator += for position
void operator += (Position& a, const Position& b) {
	a.x += b.x;
	a.y += b.y;
}

// operator -= for position
void operator -= (Position& a, const Position& b) {
	a.x -= b.x;
	a.y -= b.y;
}

// operator == for position
bool operator ==(const Position& obj1, const Position& obj2) {
	if (obj1.x == obj2.x && obj1.y == obj2.y) return true;
	else return false;
}

// costructor for position
Position::Position() {
	this->x = 0;
	this->y = 0;
}

// costructor for position
Position::Position(int x, int y) {
	this->x = x;
	this->y = y;
}
