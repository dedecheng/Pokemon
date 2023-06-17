/***********************************************************************
 * File: Player.h
 * Author: KUAN-TE CHENG (B11132007)
 * Create Date: 2023--06-14
 * Editor: KUAN-TE CHENG (B11132007)
 * Update Date: 2023--06-14
 * Description: some declaration of Player class
***********************************************************************/
#pragma once
#include "Pokemon.h"
#include "Variable.h"
#include "Potion.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Player {
private:
	int currentPokemon = 0;
	Pokemon pokemon[3];
	Potion potion[4];
public:
	//constructor
	Player();

	//Mutator
	void setPokemon(std::string name, vector<std::string> skills, vector<PokemonData> PokeLib, vector<SkillData> SkillLib);
	void initialize();

	//Accessor
	Pokemon* getAllPokemon();
	Pokemon* getOnStagePokemon() { return &pokemon[currentPokemon]; }

	// potion
	void usePotion(const string& potion, const string& pokemonName);

	//switch
	bool canSwitch(string pokemonName);
	void switchPokemon(string pokemonName);
	void switchNextPokemon();

	// check
	bool pokemonAllDead();

	/*
	Player& operator =(Player other) {
		this->currentPokemon = other.currentPokemon;
		*this->pokemon = *other.pokemon;
		*this->potion = *other.potion;
		return *this;
	}*/
};