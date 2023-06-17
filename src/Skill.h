/***********************************************************************
 * File: Skill.h
 * Author: KUAN-TE CHENG (B11132007)
 * Create Date: 2023--06-14
 * Editor: KUAN-TE CHENG (B11132007)
 * Update Date: 2023--06-14
 * Description: some declaration of Skill class
***********************************************************************/
#pragma once
#include "Variable.h"
#include <vector>
#include <string>
#include <random>

using namespace std;

class Skill : public SkillData {
private:
	SkillData data;
public:
	Skill();

	// No Con constructor
	Skill(string name, string skillType, string PS, double power, double accuracy, int usePP);
	// Has Con constructor
	Skill(string name, string skillType, string PS, double power, double accuracy, int usePP, string Con);

	//Mutator
	void setUsePP(int);
	void setData(SkillData p) { data = p; }

	// Accessor
	int getUsePP() const;
	string getCon() const;
	string getSkillName() const;
	//string getSkillType() const { return data.; }
	double getPower() const;
	double getAccuracy() const;
	bool getPS() const;
	Type getType() const;
};