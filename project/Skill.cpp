/***********************************************************************
 * File: Skill.cpp
 * Author: KUAN-TE CHENG (B11132007)
 * Create Date: 2023--06-14
 * Editor: KUAN-TE CHENG (B11132007)
 * Update Date: 2023--06-14
 * Description: some code of skill class
***********************************************************************/

#include "Skill.h"

/**
  * Intent : Change skillType from string to Type
  * Pre : string
  * Post : Type
 */
Type TypeStringToType(string skillType) {
	if ("Normal" == skillType) { return Type::NOR; }
	else if ("Fire" == skillType) { return Type::FIR; }
	else if ("Water" == skillType) { return Type::WAT; }
	else if ("Electric" == skillType) { return Type::ELE; }
	else if ("Grass" == skillType) { return Type::GRA; }
	else if ("Ice" == skillType) { return Type::ICE; }
	else if ("Fighting" == skillType) { return Type::FIG; }
	else if ("Poison" == skillType) { return Type::POI; }
	else if ("Ground" == skillType) { return Type::GRO; }
	else if ("Flying" == skillType) { return Type::FLY; }
	else if ("Physic" == skillType) { return Type::PSY; }
	else if ("Bug" == skillType) { return Type::BUG; }
	else if ("Rock" == skillType) { return Type::ROC; }
	else if ("Ghost" == skillType) { return Type::GHO; }
	else if ("Dragon" == skillType) { return Type::DRA; }
	else if ("Dark" == skillType) { return Type::DAR; }
	else if ("Steel" == skillType) { return Type::STE; }
	else if ("Fairy" == skillType) { return Type::FAI; }
	else { return Type::NOTFOUND; }
}

/**
  * Intent : Change skillType from int to Type
  * Pre : int
  * Post : Type
 */
Type intToType(int i) {
	if (1 == i) { return Type::NOR; }
	else if (2 == i) { return Type::FIR; }
	else if (3 == i) { return Type::WAT; }
	else if (4 == i) { return Type::ELE; }
	else if (5 == i) { return Type::GRA; }
	else if (6 == i) { return Type::ICE; }
	else if (7 == i) { return Type::FIG; }
	else if (8 == i) { return Type::POI; }
	else if (9 == i) { return Type::GRO; }
	else if (10 == i) { return Type::FLY; }
	else if (11 == i) { return Type::PSY; }
	else if (12 == i) { return Type::BUG; }
	else if (13 == i) { return Type::ROC; }
	else if (14 == i) { return Type::GHO; }
	else if (15 == i) { return Type::DRA; }
	else if (16 == i) { return Type::DAR; }
	else if (17 == i) { return Type::STE; }
	else if (18 == i) { return Type::FAI; }
	else
	{
		return Type::NOTFOUND;
	}
}

/**
  * Intent : Change skillType from string to int
  * Pre : string
  * Post : int
 */
int TypeStringToInt(string skillType) {
	if ("Normal" == skillType) { return 1; }
	else if ("Fire" == skillType) { return 2; }
	else if ("Water" == skillType) { return 3; }
	else if ("Electric" == skillType) { return 4; }
	else if ("Grass" == skillType) { return 5; }
	else if ("Ice" == skillType) { return 6; }
	else if ("Fighting" == skillType) { return 7; }
	else if ("Poison" == skillType) { return 8; }
	else if ("Ground" == skillType) { return 9; }
	else if ("Flying" == skillType) { return 10; }
	else if ("Physic" == skillType) { return 11; }
	else if ("Bug" == skillType) { return 12; }
	else if ("Rock" == skillType) { return 13; }
	else if ("Ghost" == skillType) { return 14; }
	else if ("Dragon" == skillType) { return 15; }
	else if ("Dark" == skillType) { return 16; }
	else if ("Steel" == skillType) { return 17; }
	else if ("Fairy" == skillType) { return 18; }
	else { return -1; }
}

/**
  * Intent : basic constructor of Skill
  * Pre : none
  * Post : none
 */
Skill::Skill() {}

/**
  * Intent : constructor of Skill which No Con
  * Pre : none
  * Post : none
 */
Skill::Skill(string name, string skillType, string PS, double power, double accuracy, int usePP) {
	data.name = name;
	data.type = TypeStringToType(skillType);
	data.power = power;
	data.accuracy = accuracy;
	data.PP = usePP;

	if (PS == "Physical") data.ps = DamageCategory::Physical;
	else if (PS == "Special") data.ps = DamageCategory::Special;
	else if (PS == "Status") data.ps = DamageCategory::Status;
}

/**
  * Intent : constructor of Skill which Has Con
  * Pre : none
  * Post : none
 */
Skill::Skill(string name, string skillType, string PS, double power, double accuracy, int usePP, string Con) {
	data.name = name;
	data.type = TypeStringToType(skillType);
	data.power = power;
	data.accuracy = accuracy;
	data.PP = usePP;
	data.con = Con;

	if (PS == "Physical") data.ps = DamageCategory::Physical;
	else if (PS == "Special") data.ps = DamageCategory::Special;
	else if (PS == "Status") data.ps = DamageCategory::Status;
}

// Accessors
int Skill::getUsePP() const { return data.PP; }

string Skill::getCon() const { return data.con; }

string Skill::getSkillName() const { return data.name; }

double Skill::getPower() const { return data.power; }

double Skill::getAccuracy() const { return data.accuracy; }

bool Skill::getPS() const { return data.ps; }

Type Skill::getType() const { return data.type; }

void Skill::setUsePP(int pp) { data.PP = pp; }
