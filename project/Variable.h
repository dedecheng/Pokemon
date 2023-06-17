/***********************************************************************
 * File: Variable.h
 * Author: KUAN-TE CHENG (B11132007)
 * Create Date: 2023--06-14
 * Editor: KUAN-TE CHENG (B11132007)
 * Update Date: 2023--06-14
 * Description: this file contain many kind of data type
***********************************************************************/
#pragma once
#include <string>
#include <vector>
#include <map>

/**
  * Intent : use this type to denote pokemon's attributes
 */
enum class Type {
	NOTFOUND = -1,
	NOR = 0,
	FIR = 1,
	WAT, ELE, GRA, ICE, FIG, POI, GRO, FLY, PSY, BUG, ROC, GHO, DRA, DAR, STE, FAI
};

/**
  * Intent : this type denotes different kind of attack
 */
enum DamageCategory {
	none = -1,
	Physical = 0,
	Special,
	Status
};

/**
  * Intent : keyboard input
 */
enum ValidInput {
	EW = 0,
	EA, ES, ED, EESC, INVALID
};

/**
  * Intent : position
 */
struct Position {
	int x, y;
	Position();
	Position(int x, int y);
};

/**
  * Intent : Position's operator overloading
 */
Position operator + (const Position& a, const Position& b);
Position operator - (const Position& a, const Position& b);
void operator += (Position& a, const Position& b);
void operator -= (Position& a, const Position& b);
bool operator ==(const Position& obj1, const Position& obj2);

/**
  * Intent : many basic datas of pokemon are stored in this struct
 */
struct PokemonData {
	std::string name;
	std::vector<Type> types;
	double maxHp, hp, atk, def, spAtk, spDef, speed;

	//operator overloading =
	void operator =(PokemonData p)
	{
		name = p.name;
		types = p.types;
		maxHp = p.maxHp;
		hp = p.hp;
		atk = p.atk;
		def = p.def;
		spAtk = p.spAtk;
		spDef = p.spDef;
		speed = p.speed;
	}

	//constructor
	PokemonData()
	{
		name = "";
		types.clear();
		maxHp = 0;
		hp = 0;
		atk = 0;
		def = 0;
		spAtk = 0;
		spDef = 0;
		speed = 0;
	}
};

/**
  * Intent : many basic datas of skill are stored in this struct
 */
struct SkillData {
	std::string name;
	int PP;
	Type type;
	DamageCategory ps; // enum DamageCategory
	double power, accuracy;
	std::string con;

	//operator overloading =
	void operator =(SkillData& p)
	{
		name = p.name;
		type = p.type;
		ps = p.ps;
		power = p.power;
		accuracy = p.accuracy;
		PP = p.PP;
		con = p.con;
	}

	//constructor
	SkillData()
	{
		name = "";
		type = Type::NOTFOUND;
		ps = DamageCategory::none;
		power = 0;
		accuracy = 0;
		PP = 0;
		con = "";
	}
};
