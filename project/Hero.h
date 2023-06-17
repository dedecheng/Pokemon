/***********************************************************************
 * File: Hero.h
 * Author: Tone-yeah (B11132013)
 * Create Date: 2023--06-14
 * Editor: Tone-yeah (B11132013)
 * Update Date: 2023--06-14
 * Description: RPG player class for Game class. Game control main process.
***********************************************************************/

#pragma once
#include <string>
#include "Variable.h"
#include "main.h"

class Hero {

private:
	Position	sPos;			// Hero location
	char sIcon = 'H';	// Hero icon
public:
	// Default constructor
	Hero() {
		this->sPos.x = 0;
		this->sPos.y = 0;
		this->sIcon = 'H';
	};
	// Setting constructor
	Hero(int x, int y, char icon = 'H') {
		this->sPos.x = x;
		this->sPos.y = y;
		this->sIcon = icon;
	};

	// Setting constructor
	Hero(Position& pos, char icon = 'H') {
		this->sPos = pos;
		this->sIcon = icon;
	};

	// Set position
	void setPos(Position pos) { this->sPos = pos; }
	void setPos(int x, int y) {
		this->sPos.x = x;
		this->sPos.y = y;
	}

	// Set icon
	void setIcon(char& icon) { this->sIcon = icon; }

	// Get position
	Position getPos(void) { return this->sPos; }

	// Get Icon
	char getIcon(void) { return this->sIcon; }

	// Incrementally move the elements 
	void move(Position delta) {
		// Compute the next position
		Position next = this->sPos + delta;

		if (isPositionValid(next))
			this->sPos = next;
		else {
			std::cout << "Invalid location\n";
		}
	}
};
