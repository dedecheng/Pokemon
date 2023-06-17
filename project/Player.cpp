/***********************************************************************
 * File: Player.cpp
 * Author: KUAN-TE CHENG (B11132007)
 * Create Date: 2023--06-14
 * Editor: KUAN-TE CHENG (B11132007)
 * Update Date: 2023--06-14
 * Description: some code of Player class.
***********************************************************************/
#include "Player.h"

/**
  * Intent : set player's pokemon's data
  * Pre : pokemon's name, it's skills, pokemon library, skill library
  * Post : none
 */
void Player::setPokemon(std::string name, vector<std::string> skills, vector<PokemonData> PokeLib, vector<SkillData> SkillLib) {
	//find the pokemon we want from library and set the data to player's pokemon
	for (unsigned int i = 0; i < PokeLib.size(); i++) {
		if (name == PokeLib[i].name) {
			pokemon[currentPokemon].setFainted(0);
			pokemon[currentPokemon] = PokeLib[i];
			pokemon[currentPokemon].setSkills(skills, SkillLib);
		}
	}
	currentPokemon++;
	currentPokemon %= 3;
}

/**
  * Intent : initialize player's current pokemon and potions
  * Pre : none
  * Post : none
 */
void Player::initialize() {
	this->currentPokemon = 0;

	potion[0].setName("Potion");
	potion[1].setName("SuperPotion");
	potion[2].setName("HyperPotion");
	potion[3].setName("MaxPotion");

	potion[0].setHeal(20);
	potion[1].setHeal(60);
	potion[2].setHeal(120);
	potion[3].setHeal(10000);
}

/**
  * Intent : switch Next Pokemon
  * Pre : none
  * Post : none
 */
void Player::switchNextPokemon()
{
	currentPokemon++;
	currentPokemon %= 3;
}

/**
  * Intent : use potion, heal pokemon
  * Pre : potion name, pokemon name
  * Post : none
 */
void Player::usePotion(const string& potion, const string& pokemonName) {
	//get potion's recovery amount
	int heal;
	for (int i = 0; i < 4; i++) {
		if (potion == this->potion[i].getName()) heal = this->potion[i].getHeal();
	}

	//find pokemone and heal it
	int health;
	for (int i = 0; i < 3; i++) {
		if (pokemonName == this->pokemon[i].getPokemonName()) {
			health = this->pokemon[i].getPokemonHp();
			health += heal;
			//make sure not exceed maxHP
			if (health > this->pokemon[i].getPokemonMaxHp()) {
				health = this->pokemon[i].getPokemonMaxHp();
			}
			this->pokemon[i].setPokemonHp(health);
		}
	}
}

/**
  * Intent : test if pokemon can switch
  * Pre : pokemon name
  * Post : bool
 */
bool Player::canSwitch(string pokemonName)
{
	for (int i = 0; i < 3; i++)
	{
		if (i == currentPokemon)continue;

		//pokemaon exist and not fainted
		if (pokemon[i].name == pokemonName && !pokemon[i].getFainted())
		{
			return true;
		}
	}
	return false;
}

/**
  * Intent : switch pokemon
  * Pre : pokemon's name
  * Post : none
 */
void Player::switchPokemon(string pokemonName)
{
	for (int i = 0; i < 3; i++)
	{
		if (pokemon[i].name == pokemonName) currentPokemon = i;
	}
}

/**
  * Intent : player's basic constructor
  * Pre : none
  * Post : none
 */
Player::Player() {
	this->currentPokemon = 0;
	for (int i = 0; i < 3; i++) {
		pokemon[i] = Pokemon();
	}

	for (int i = 0; i < 4; i++) {
		potion[i] = Potion();
	}
}

/**
  * Intent : see if all player's pokemons are dead
  * Pre : none
  * Post : bool
 */
bool Player::pokemonAllDead() {
	bool allDead = true;
	for (int i = 0; i < 3; i++) {
		if (!pokemon[i].getFainted()) allDead = false;
	}

	if (allDead) return true;
	else return false;
}

/**
  * Intent : get all pokemon
  * Pre : none
  * Post : pokemons' array
 */
Pokemon* Player::getAllPokemon() {
	return pokemon;
}
