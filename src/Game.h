/***********************************************************************
 * File: Game.h
 * Author: Raymin, Tone-yeah
 * Create Date: 2023--06-14
 * Editor: Raymin, Tone-yeah
 * Update Date: 2023--06-14
 * Description: some declaration of Game class. Game control main process.
***********************************************************************/
#pragma once

#include "Variable.h"
#include "Player.h"
#include "Skill.h"
#include "color.h"
#include "Sound.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <random>
#include <cstdlib>

using namespace std;

const int TOTALTYPE = 18;

class Game {
private:
	vector<PokemonData> pokemonLib;
	vector<SkillData> moveLib;
	vector<string> TestCommandLib; // For Test mode
	Player me;
	Player enemy;
	int turns;
	bool testMode;
	double typeChart[TOTALTYPE][TOTALTYPE] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,0.5,0,1,1,0.5,1},
		{1,0.5,0.5,1,2,2,1,1,1,1,1,2,0.5,1,0.5,1,2,1},
		{1,2,0.5,1,0.5,1,1,1,2,1,1,1,2,1,0.5,1,1,1},
		{1,1,2,0.5,0.5,1,1,1,0,2,1,1,1,1,0.5,1,1,1},
		{1,0.5,2,1,0.5,1,1,0.5,2,0.5,1,0.5,2,1,0.5,1,0.5,1},
		{1,0.5,0.5,1,2,0.5,1,1,2,2,1,1,1,1,2,1,0.5,1},
		{2,1,1,1,1,2,1,0.5,1,0.5,0.5,0.5,2,0,1,2,2,0.5},
		{1,1,1,1,2,1,1,0.5,0.5,1,1,1,0.5,0.5,1,1,0,2},
		{1,2,1,2,0.5,1,1,2,1,0,1,0.5,2,1,1,1,2,1},
		{1,1,1,0.5,2,1,2,1,1,1,1,2,0.5,1,1,1,0.5,1},
		{1,1,1,1,1,1,2,2,1,1,0.5,1,1,1,1,0,0.5,1},
		{1,0.5,1,1,2,1,0.5,0.5,1,0.5,2,1,1,0.5,1,2,0.5,0.5},
		{1,2,1,1,1,2,0.5,1,0.5,2,1,2,1,1,1,1,0.5,1},
		{0,1,1,1,1,1,1,1,1,1,2,1,1,2,1,0.5,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,0.5,0},
		{1,1,1,1,1,1,0.5,1,1,1,2,1,1,2,1,0.5,1,0.5},
		{1,0.5,0.5,0.5,1,2,1,1,1,1,1,1,2,1,1,1,0.5,2},
		{1,0.5,1,1,1,1,2,0.5,1,1,1,1,1,1,2,2,0.5,1}
	};
	const int criticalRate = 24;

	void meUseSkill(const string&);
	void enemyUseSkill(const string&);
	void BandP();
	void fileModeupdate();
	void cinModeupdate();
	bool meFirst();
	bool gameover();

	// For cinMode 
private:
	vector<vector<char>> gameboard;
	Position playerPos = { 8,8 };
	char playerIcon = 'P';

public:
	Game();

	// file I/O
	bool canOpen(string fileName);
	void readPokemonLib(string fileName);
	void readMoveLib(string fileName);
	void readGameData(string fileName);
	// void readTestCommand(string fileName);

	// Game start, for non-user
	void startGame(string fileName);
	void startGame(char);

	// Command
	void Test();
	void Battle(ifstream& file);
	void Battle();
	void Bag(ifstream& file);
	void Bag();
	void switchPokemon(ifstream& file);
	void switchPokemon();
	void Status();
	void check();

	//output
	void coutInfo(string);

	PokemonData searchPokemonLib(string name);
	SkillData searchMoveLib(string name);
};


