/***********************************************************************
 * File: Potion.h
 * Author: KUAN-TE CHENG (B11132007)
 * Create Date: 2023--06-14
 * Editor: KUAN-TE CHENG (B11132007)
 * Update Date: 2023--06-14
 * Description: some declaration of Potion class
***********************************************************************/
#pragma once
#include <string>

class Potion {
private:
	std::string name;
	int heal;
public:
	//Mutator
	void setName(std::string name) { this->name = name; }
	void setHeal(int heal) { this->heal = heal; }

	//Accessor
	std::string getName() const { return name; }
	int getHeal() const { return heal; }
	int getHealAmount() const { return heal; }
};
