/***********************************************************************
 * File: Pokemon.cpp
 * Author: KUAN-TE CHENG (B11132007)
 * Create Date: 2023--06-14
 * Editor: KUAN-TE CHENG (B11132007)
 * Update Date: 2023--06-14
 * Description: some code of Pokemon class.
***********************************************************************/
#include "Pokemon.h"
#include "Variable.h"
#include "Skill.h"

/**
  * Intent : basic constructor of Pokemon
  * Pre : none
  * Post : none
 */
Pokemon::Pokemon()
{
	name = "";
	Con = "";
	types.clear();
	maxHp = 0;
	hp = 0;
	atk = 0;
	def = 0;
	spAtk = 0;
	spDef = 0;
	speed = 0;
	fainted = 0;
}

/**
  * Intent : set Pokemon's skills
  * Pre : skills' names, skill's data base
  * Post : none
 */
void Pokemon::setSkills(vector<string> skills_names, vector<SkillData> skill_db)
{
	int size = 4;
	int db_idx[4] = {};
	int count = 0;

	//go through skill_db and find correspond index
	for (auto u : skill_db)
	{
		for (int i = 0; i < size; i++)
		{
			if (u.name == skills_names[i])
			{
				db_idx[i] = count;
			}
		}
		count++;
	}

	//use idx that we found to set skills' data
	for (int i = 0; i < size; i++)
	{
		skills[i].setData(skill_db[db_idx[i]]);
	}
}

/**
  * Intent : Mutator of Pokemon's name
  * Pre : string
  * Post : none
 */
void Pokemon::setPokemonName(string s)
{
	name = s;
}

/**
  * Intent : Mutator of Pokemon's types
  * Pre :types
  * Post : none
 */
void Pokemon::setPokemonTypes(vector<Type> v)
{
	types = v;
}

/**
  * Intent : Mutator of Pokemon's maxHp
  * Pre : double
  * Post : none
 */
void Pokemon::setPokemonMaxHp(double d)
{
	maxHp = d;
}

/**
  * Intent : Mutator of Pokemon's hp
  * Pre : double
  * Post : none
 */
void Pokemon::setPokemonHp(double d)
{
	hp = d;
}

/**
  * Intent : Mutator of Pokemon's atk
  * Pre : double
  * Post : none
 */
void Pokemon::setPokemonAtk(double d)
{
	atk = d;
}

/**
  * Intent : Mutator of Pokemon's def
  * Pre : double
  * Post : none
 */
void Pokemon::setPokemonDef(double d)
{
	def = d;
}

/**
  * Intent : Mutator of Pokemon's spAtk
  * Pre : double
  * Post : none
 */
void Pokemon::setPokemonSpAtk(double d)
{
	spAtk = d;
}

/**
  * Intent : Mutator of Pokemon's spDef
  * Pre : double
  * Post : none
 */
void Pokemon::setPokemonSpDef(double d)
{
	spDef = d;
}

/**
  * Intent : Mutator of Pokemon's speed
  * Pre : double
  * Post : none
 */
void Pokemon::setPokemonSpeed(double d)
{
	speed = d;
}

/**
  * Intent : Mutator of Pokemon's fainted
  * Pre : bool
  * Post : none
 */
void Pokemon::setFainted(bool tof)
{
	fainted = tof;
}

/**
  * Intent : Accessor of Pokemon's name
  * Pre : none
  * Post : string
 */
string Pokemon::getPokemonName()
{
	return name;
}

/**
  * Intent : Accessor of Pokemon's types
  * Pre : none
  * Post : types
 */
vector<Type> Pokemon::getPokemonTypes()
{
	return types;
}

/**
  * Intent : Accessor of Pokemon's hp
  * Pre : none
  * Post : double
 */
int Pokemon::getPokemonHp()
{
	return hp;
}

/**
  * Intent : Accessor of Pokemon's atk
  * Pre : none
  * Post : double
 */
double Pokemon::getPokemonAtk()
{
	return atk;
}

/**
  * Intent : Accessor of Pokemon's def
  * Pre : none
  * Post : double
 */
double Pokemon::getPokemonDef()
{
	return def;
}

/**
  * Intent : Accessor of Pokemon's spAtk
  * Pre : none
  * Post : double
 */
double Pokemon::getPokemonSpAtk()
{
	return spAtk;
}

/**
  * Intent : Accessor of Pokemon's spDef
  * Pre : none
  * Post : double
 */
double Pokemon::getPokemonSpDef()
{
	return spDef;
}

/**
  * Intent : Accessor of Pokemon's speed
  * Pre : none
  * Post : double
 */
double Pokemon::getPokemonSpeed()
{
	return speed;
}

/**
  * Intent : use name to get the skill you want
  * Pre : skill name
  * Post : skill's pointer
 */
Skill* Pokemon::getSkill(const string& skill_name)
{
	int size = 4;
	for (int i = 0; i < 4; i++)
	{
		if (skills[i].getSkillName() == skill_name)
		{
			return &skills[i];
		}
	}
}

/**
  * Intent : get all skill
  * Pre : none
  * Post : skill's array
 */
Skill* Pokemon::getAllSkills()
{
	return skills;
}

/**
  * Intent : get fainted
  * Pre : none
  * Post : bool
 */
bool Pokemon::getFainted()
{
	return fainted;
}

/**
  * Intent : get condition
  * Pre : none
  * Post : con(string)
 */
string Pokemon::getCondition() {
	return Con;
}

/**
  * Intent : get maxHP
  * Pre : none
  * Post : maxHP(int)
 */
int Pokemon::getPokemonMaxHp() {
	return maxHp;
}

/**
  * Intent : add condition
  * Pre : con(string)
  * Post : none
 */
void Pokemon::plusCondition(const string& con) {
	if (Con.size() != 0) Con += " ";
	Con += con;
}
