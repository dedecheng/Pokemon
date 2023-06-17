/***********************************************************************
 * File: Pokemon.h
 * Author: KUAN-TE CHENG (B11132007)
 * Create Date: 2023--06-14
 * Editor: KUAN-TE CHENG (B11132007)
 * Update Date: 2023--06-14
 * Description: some declaration of Pokemon class
***********************************************************************/
#pragma once
#include "Variable.h"
#include "Skill.h"
#include <vector>
#include <string>

using namespace std;

class Pokemon :public PokemonData {
private:
	std::string Con;
	Skill skills[4];
	bool fainted;
public:
	//constructor
	Pokemon();

	//Mutator
	void setSkills(vector<string>, vector<SkillData>);
	void setPokemonName(string);
	void setPokemonTypes(vector<Type>);
	void setPokemonMaxHp(double);
	void setPokemonHp(double);
	void setPokemonAtk(double);
	void setPokemonDef(double);
	void setPokemonSpAtk(double);
	void setPokemonSpDef(double);
	void setPokemonSpeed(double);
	void setFainted(bool);
	void plusCondition(const string&);


	//Accessor
	string getPokemonName();
	vector<Type> getPokemonTypes();
	int getPokemonMaxHp();
	int getPokemonHp();
	double getPokemonAtk();
	double getPokemonDef();
	double getPokemonSpAtk();
	double getPokemonSpDef();
	double getPokemonSpeed();
	Skill* getSkill(const string&);
	Skill* getAllSkills();
	bool getFainted();
	string getCondition();

	//operator overloading
	Pokemon& operator = (PokemonData poke) {
		this->name = poke.name;
		this->types = poke.types;
		this->maxHp = poke.maxHp;
		this->hp = poke.hp;
		this->atk = poke.atk;
		this->def = poke.def;
		this->spAtk = poke.spAtk;
		this->spDef = poke.spDef;
		this->speed = poke.speed;

		return *this;
	}
};