/***********************************************************************
 * File: Game.cpp
 * Author: Raymin (B11132009) Tone-yeah (B11132013)
 * Create Date: 2023--06-14
 * Editor: Raymin (B11132009) Tone-yeah (B11132013)
 * Update Date: 2023--06-14
 * Description: main for whole program
***********************************************************************/

#include "Game.h"
#include "Sound.h"
#include "Hero.h"

#include <iostream>
#include <random>
#include <conio.h>
#include <vector>

using namespace std;

// Constent value
const char GWALL = 'O';
const char GNOTHING = ' ';

int GWIDTH = 15;
int GHEIGHT = 15;
const int MIN_SIZE = 4;
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

Hero hero(7, 7, 'H');

vector <vector<char>> gBoard;

void RunTestMode();
void RPG();

void keyUpdate(bool key[]);
void setupBoard(int rowN, int colN);
void draw(void);

void update(bool key[]);

int main() {

	while (true) {
		cout << "Select Game Mode (1 for File mode, 2 for User Input mode)" << endl;
		char mode = _getch();
		system("CLS");
		if (mode == '1') { RunTestMode(); break; }
		else if (mode == '2') { RPG(); break; }
		else { cout << "Invalid Input" << endl; }
	}
	return 0;
}

// function for RunTestMode in game class
void RunTestMode() {
	// play music
	playBackgroundMusic();
	Game game;
	cout << "This the file reading mode" << endl;
	while (true) {
		string fileName;
		cout << "Input the file name" << endl; // ex: case1
		cin >> fileName;
		if (game.canOpen(fileName)) { game.startGame(fileName); break; }
		else { cout << "Wrong file name, please type again" << endl; }
	}
}

// function for RunTestMode in game class
void RPG() {
	// play music
	playBackgroundMusic();

	srand(time(NULL));

	bool gKeyState[ValidInput::INVALID];
	for (int i = 0; i < ValidInput::INVALID; i++) {
		gKeyState[i] = false;
	}
	setupBoard(GWIDTH, GHEIGHT);
	// Draw the board and information
	draw();

	clock_t startT, endT;
	startT = clock();
	endT = clock();


	while (!gKeyState[ValidInput::EESC]) {

		// Compute the time lap
		double timeFrame = (double)(endT - startT) / CLOCKS_PER_SEC;

		// Execute the game loop
		if (timeFrame >= gTimeLog) {
			update(gKeyState);
			startT = clock();
		}

		// Update the key
		keyUpdate(gKeyState);
		endT = clock();
	}
}

// function for user key input
void keyUpdate(bool key[])
{
	for (int i = 0; i < ValidInput::INVALID; i++) {
		key[i] = false;
	}
	char input = _getch();
	switch (input) {
	case 'w': case 'W':
		key[ValidInput::EW] = true;
		break;
	case 'A': case 'a':
		key[ValidInput::EA] = true;
		break;
	case 'S': case 's':
		key[ValidInput::ES] = true;
		break;
	case 'D': case 'd':
		key[ValidInput::ED] = true;
		break;
	case 27:
		key[ValidInput::EESC] = true;
		break;
	default:
		key[ValidInput::INVALID] = true;
		break;
	}
}

// set up the board that user can walk through
void setupBoard(int rowN, int colN)
{
	gBoard.clear();

	gBoard.resize(colN);
	for (int i = 0; i < colN; i++) {
		gBoard[i].resize(rowN);
	}

	for (int i = 0; i < colN; i++) {
		for (int j = 0; j < rowN; j++) {
			if (i == 0 || i == colN - 1 || j == 0 || j == rowN - 1)
				gBoard[i][j] = GWALL;
			else
				gBoard[i][j] = GNOTHING;
		}
	}
}

// draw the board
void draw()
{
	system("CLS");

	std::vector<std::vector<char>> drawBoard(GHEIGHT);

	for (int i = 0; i < GHEIGHT; i++) {
		drawBoard[i].resize(GWIDTH);
		for (int j = 0; j < GWIDTH; j++) {
			drawBoard[i][j] = gBoard[i][j];
		}
	}

	drawBoard[3][3] = '1';
	drawBoard[3][11] = '2';
	drawBoard[11][3] = '3';
	drawBoard[11][11] = '4';
	if (hero.getPos() == Position(3, 3) || hero.getPos() == Position(3, 11) || hero.getPos() == Position(11, 3) || hero.getPos() == Position(11, 11))
		drawBoard[hero.getPos().y][hero.getPos().x] = '!';
	else drawBoard[hero.getPos().y][hero.getPos().x] = hero.getIcon();

	// Draw the board
	for (int i = 0; i < GHEIGHT; i++) {
		for (int j = 0; j < GWIDTH; j++) {
			if (drawBoard[i][j] == GWALL) {
				std::cout << WHITE_BG << drawBoard[i][j] << RESET;
			}
			else if (drawBoard[i][j] == '1') {
				std::cout << RED << drawBoard[i][j] << RESET;
			}
			else if (drawBoard[i][j] == '2') {
				std::cout << GREEN << drawBoard[i][j] << RESET;
			}
			else if (drawBoard[i][j] == '3') {
				std::cout << BLUE << drawBoard[i][j] << RESET;
			}
			else if (drawBoard[i][j] == '4') {
				std::cout << YELLOW << drawBoard[i][j] << RESET;
			}
			else {
				std::cout << drawBoard[i][j]; 
			}
		}
		std::cout << std::endl;
	}
}

// hero move via reading key information
void update(bool key[])
{
	// 清除版面
	system("CLS");

	Position delta(0, 0);

	// 是否有input
	bool hasInput = false;
	if (key[ValidInput::EW]) {
		delta -= Position(0, 1);
		hasInput = true;
	}
	else if (key[ValidInput::ES]) {
		delta += Position(0, 1);
		hasInput = true;
	}
	else if (key[ValidInput::EA]) {
		delta = delta - Position(1, 0);
		hasInput = true;
	}
	else if (key[ValidInput::ED]) {
		delta = delta + Position(1, 0);
		hasInput = true;
	}
	else {
		bool allInvalid = true;
		for (int i = 0; i < ValidInput::INVALID; i++) {
			if (key[i]) {
				allInvalid = false;
				break;
			}
		}
		if (allInvalid)
			std::cout << "invalid input\n";
	}

	if (hasInput) {
		hero.move(delta);
	}

	if (hero.getPos() == Position(3, 3)) {
		Game game;
		game.startGame('1');
	}
	else if (hero.getPos() == Position(3, 11)) {
		Game game;
		game.startGame('2');
	}
	else if (hero.getPos() == Position(11, 3)) {
		Game game;
		game.startGame('3');
	}
	else if (hero.getPos() == Position(11, 11)) {
		Game game;
		game.startGame('4');
	}

	draw();
}

// check for the validation for hero move
bool isPositionValid(Position& pos)
{
	if (gBoard[pos.y][pos.x] != GNOTHING)
		return false;
	else return true;
}