/***********************************************************************
 * File: Game.cpp
 * Author: Raymin (B11132009) Tone-yeah (B11132013)
 * Create Date: 2023--06-14
 * Editor: Raymin (B11132009) Tone-yeah (B11132013)
 * Update Date: 2023--06-14
 * Description: some method of Game class. Game control main process.
***********************************************************************/

#include "Game.h"

// type conversion for enum Type
void to_Type(std::string index, Type& type);

// type conversion for enum DamageCategory
DamageCategory whichCategory(std::string str);

// constructor for game class
Game::Game() : turns(0) {}

// type conversion for enum Type (enum Type version)
void to_Type(string index, Type& type) {
	// Type dictionary
	std::map<string, Type> dic =
	{ {"Normal", Type::NOR}, {"Fire", Type::FIR}, {"Water", Type::WAT}, {"Electric", Type::ELE},
	{"Grass", Type::GRA}, {"Ice", Type::ICE}, {"Fighting", Type::FIG}, {"Poison", Type::POI},
	{"Ground", Type::GRO}, {"Flying", Type::FLY}, {"Psychic", Type::PSY}, {"Bug", Type::BUG},
	{"Rock", Type::ROC}, {"Ghost", Type::GHO}, {"Dragon", Type::DRA}, {"Dark", Type::DAR},
	{"Steel", Type::STE}, {"Fairy", Type::FAI} };

	// search if index exist, if no than return Type::NOTFOUND
	if (dic.find(index) != dic.end()) { type = dic[index]; }
	else { type = Type::NOTFOUND; }
}

// type conversion for enum Type (integer version)
void to_TypeInt(string index, int& type) {
	// Type dictionary
	std::map<string, int> dic =
	{ {"Normal", 0}, {"Fire", 1}, {"Water", 2}, {"Electric", 3},
	{"Grass", 4}, {"Ice", 5}, {"Fighting", 6}, {"Poison", 7},
	{"Ground", 8}, {"Flying", 9}, {"Psychic", 10}, {"Bug", 11},
	{"Rock", 12}, {"Ghost", 13}, {"Dragon", 14}, {"Dark", 15},
	{"Steel", 16}, {"Fairy", 17} };

	// search if index exist, if no than return Type::NOTFOUND
	if (dic.find(index) != dic.end()) { type = dic[index]; }
	else { type = -1; }
}

// type conversion for enum DamageCategory
DamageCategory whichCategory(std::string str) {
	if (str == "Physical") { return DamageCategory::Physical; }
	else if (str == "Special") { return DamageCategory::Special; }
	else return DamageCategory::Status;
}

// print turns for consoles
void Game::coutInfo(string s)
{
	cout << "[Turn " << turns << "] " << s << endl;
}

// search PokemonLib using name
PokemonData Game::searchPokemonLib(string name) {
	for (unsigned int i = 0; i < this->pokemonLib.size(); i++) {
		if (this->pokemonLib[i].name == name) { return this->pokemonLib[i]; };
	}

	cout << "ERROR: Name is not Found in Game::searchPokemonLib" << endl;
	PokemonData a;
	return a;
}

// search MoveLib using name
SkillData Game::searchMoveLib(string name) {
	for (unsigned int i = 0; i < this->pokemonLib.size(); i++) {
		if (this->moveLib[i].name == name) { return this->moveLib[i]; };
	}

	cout << "ERROR: Skill Name is not Found in Game::searchSkillLib" << endl;
	SkillData a;
	return a;
}

// return file open validation
bool Game::canOpen(string fileName) {
	fstream file;
	file.open(fileName);
	bool canOpen = file.is_open();
	if (canOpen) { file.close(); }
	return canOpen;
}

// read Pokemon Info from file
void Game::readPokemonLib(string fileName) {
	ifstream file;
	file.open(fileName);

	string name;
	while (file >> name) {
		// Data
		PokemonData data;

		// Read: name
		data.name = name;

		// Read: Type
		int total;
		file >> total;
		for (int i = 0; i < total; i++) {
			string attrStr;
			file >> attrStr;

			Type attrType;
			to_Type(attrStr, attrType);
			if (attrType == Type::NOTFOUND) { cout << "FILE READ ERROR in readPokemonLib" << endl; } // Debug message

			// Push_back
			data.types.push_back(attrType);
		}

		// Read: HP Atk Def Sp.Atk Sp.Def Speed
		file >> data.hp >> data.atk >> data.def >> data.spAtk >> data.spDef >> data.speed;
		data.maxHp = data.hp;

		// Push into Dictionary
		this->pokemonLib.push_back(data);
	}
}

// read Pokemon move/skill from file
// Note：may change to cin, but done TESTing
void Game::readMoveLib(string fileName) { // stringstream may cause bug
	ifstream file;
	file.open(fileName);
	while (!file.eof()) {
		SkillData data;

		// Input
		string input;
		getline(file, input);
		std::stringstream ss(input);

		// String Manipulation
		string Movetype, physical;

		// Read: Move Type P/S power accuracy PP <Con>
		ss >> data.name >> Movetype >> physical >> data.power >> data.accuracy >> data.PP;
		if (!ss.str().empty()) { ss >> data.con; }
		Type type;
		to_Type(Movetype, type);
		data.type = type;
		data.ps = whichCategory(physical);

		this->moveLib.push_back(data);
	}
}

// read user's Info from file
// Need TEST
void Game::readGameData(string fileName) {
	ifstream file;
	file.open(fileName);

	while (!file.eof()) {

		for (int k = 0; k < 2; k++) {
			int pokemons; // pokemons -> 3
			file >> pokemons; // Get the number of pokemons player have

			for (int i = 0; i < pokemons; i++) {
				std::vector<std::string> skills;

				string name;
				int moves;
				file >> name >> moves; // Get the information of pokemon
				for (int j = 0; j < moves; j++) {
					string move;
					file >> move;
					skills.push_back(move);
				}

				// add into player
				if (k == 0) {
					this->me.setPokemon(name, skills, this->pokemonLib, this->moveLib);
				}
				else if (k == 1) {
					this->enemy.setPokemon(name, skills, this->pokemonLib, this->moveLib);
				}
			}
		}
	}
}

// read game running from file
// Need TEST -> start test mode
void Game::startGame(string fileName) {
	testMode = false;
	srand(time(NULL));
	ifstream file;
	file.open(fileName);

	// .txt read-in
	for (int i = 0; i < 3; i++) {
		string subfileName;
		file >> subfileName;
		if (i == 0) { this->readPokemonLib(subfileName); }
		else if (i == 1) { this->readMoveLib(subfileName); }
		else if (i == 2) { this->readGameData(subfileName); }
		else { cout << "ERROR @_@" << endl; }
	}

	// some initialize
	me.initialize();
	enemy.initialize();

	// command read-in & selection

	turns = 1;
	while (true) {
		string command;
		file >> command;
		if (command == "Test") { this->Test(); }
		else if (command == "Battle") { this->Battle(file); ++turns; }
		else if (command == "Bag") { this->Bag(file); ++turns; }
		else if (command == "Pokemon") { this->switchPokemon(file); ++turns; }
		else if (command == "Status") { this->Status(); }
		else if (command == "Check") { this->check(); }
		else if (command == "Run") { break; }
		else { cout << "Invalid command @_@" << endl; }

		if (gameover() || file.eof()) {
			// output which player win
			if (me.pokemonAllDead()) cout << "you lose!";
			else if (enemy.pokemonAllDead()) cout << "you win!";
			break;
		}
	}

	file.close();
	system("pause");
	return;
}

// read game running from cin
void Game::startGame(char boss) {

	// play music
	playBattleMusic();

	testMode = false;
	srand(time(NULL));
	string PokeLib = "PokemonLib.txt", MoveLib = "MoveLib.txt", gameData;;
	readPokemonLib(PokeLib);
	readMoveLib(MoveLib);

	if (boss == '1') gameData = "GameData1.txt";
	else if (boss == '2') gameData = "GameData2.txt";
	else if (boss == '3') gameData = "GameData3.txt";
	else if (boss == '4') gameData = "GameData4.txt";
	readGameData(gameData);

	// some initialize
	me.initialize();
	enemy.initialize();

	// command read-in & selection

	turns = 1;
	while (true) {
		system("CLS");
		cout << me.getOnStagePokemon()->getPokemonName() << " " << to_string(me.getOnStagePokemon()->getPokemonHp()) << "/"
			<< to_string(me.getOnStagePokemon()->getPokemonMaxHp()) << " " << me.getOnStagePokemon()->getCondition() << "  v.s. " << enemy.getOnStagePokemon()->getPokemonName()
			<< " " << to_string(enemy.getOnStagePokemon()->getPokemonHp()) << "/"
			<< to_string(enemy.getOnStagePokemon()->getPokemonMaxHp()) << " " << enemy.getOnStagePokemon()->getCondition() << endl;

		cout << "input (1) to Battle, (2) to switch Pokemon, (3) to open bag, (4) to run: ";
		string command;
		char c;
		while (1) {
			cin >> c;
			if (c == '1') {
				command = "Battle";
				break;
			}
			else if (c == '2') {
				command = "Pokemon";
				break;
			}
			else if (c == '3') {
				command = "Bag";
				break;
			}
			else if (c == '4') {
				command = "Run";
				break;
			}
			else {
				cout << "invalid input\n";
			}
		}

		bool ifRun = false;
		if (command == "Test") { this->Test(); }
		else if (command == "Battle") { this->Battle(); ++turns; }
		else if (command == "Bag") { this->Bag(); ++turns; }
		else if (command == "Pokemon") { this->switchPokemon(); ++turns; }
		else if (command == "Run") { 
			ifRun = true;
			cout << "you lose\n";
			system("pause");
			break; 
		}
		else { cout << "Invalid command @_@" << endl; }
		system("pause");

		if (gameover()) {
			// output which player win
			if (me.pokemonAllDead()) cout << "you lose!";
			else if (enemy.pokemonAllDead()) cout << "you win!";
			system("pause");
			break;
		}
		else if (ifRun) { break; }
	}
	// play music
	playBackgroundMusic();
	return;
}

/**
  * Intent : set testMode true
  * Pre : none
  * Post : none
 */
void Game::Test() {
	testMode = true;
}

// Battle control for me and enemy
void Game::Battle(ifstream& file) {
	// find turn(speed)
	string mySkillName, enemySkillName;
	file >> mySkillName >> enemySkillName;

	if (meFirst()) {
		meUseSkill(mySkillName);
		enemyUseSkill(enemySkillName);
	}
	else {
		enemyUseSkill(enemySkillName);
		meUseSkill(mySkillName);
	}
	BandP();
	fileModeupdate();
}

/**
  * Intent : battle for cin mode
  * Pre : none
  * Post : none
 */
void Game::Battle() {
	system("CLS");
	cout << me.getOnStagePokemon()->getPokemonName() << " has 4 skills" << endl;

	Skill* mySkills = me.getOnStagePokemon()->getAllSkills();
	for (int i = 0; i < 4; i++) {
		cout << i + 1 << ": " << mySkills[i].getSkillName() << " " << to_string(mySkills[i].getUsePP()) << ", ";
	}
	cout << endl;

	cout << "input the corresponding number to use skill:\n";
	char c;
	string mySkillName;
	while (1) {
		cin >> c;
		if (c == '1') {
			mySkillName = mySkills[0].getSkillName();
			break;
		}
		else if (c == '2') {
			mySkillName = mySkills[1].getSkillName();
			break;
		}
		else if (c == '3') {
			mySkillName = mySkills[2].getSkillName();
			break;
		}
		else if (c == '4') {
			mySkillName = mySkills[3].getSkillName();
			break;
		}
		else {
			cout << "invalid input\n";
		}
	}

	Skill* enemySkills = enemy.getOnStagePokemon()->getAllSkills();
	string enemySkillName = enemySkills[rand() % 4].getSkillName();

	if (meFirst()) {
		meUseSkill(mySkillName);
		enemyUseSkill(enemySkillName);
	}
	else {
		enemyUseSkill(enemySkillName);
		meUseSkill(mySkillName);
	}
	BandP();
	cinModeupdate();
}

// pass potion name & pokemon name into player, then health
void Game::Bag(ifstream& file) {
	// pass potion name & pokemon name into player, then health
	string potion, pokemonName, skillName;
	file.ignore();
	getline(file, potion);
	file >> pokemonName >> skillName;

	me.usePotion(potion, pokemonName);

	// output potion info
	string s;
	s = "You used a " + potion + "!";
	coutInfo(s);
	s = pokemonName + " had its HP restored.";
	coutInfo(s);

	enemyUseSkill(skillName);
	BandP();
	fileModeupdate();
}

//use cin getting potion name & pokemon name into player, then health
void Game::Bag() {
	// pass potion name & pokemon name into player, then health
	string pokemonName = me.getOnStagePokemon()->getPokemonName();
	system("CLS");
	cout << "you have 4 postions" << endl;
	cout << "1: Potion, 2: Super Potion, 3: Hyper Potion, 4: Max Potion\n";
	cout << "input the corresponding number to use potion:\n";
	char c;
	string potion;
	while (1) {
		cin >> c;
		if (c == '1') {
			potion = "Potion";
			break;
		}
		else if (c == '2') {
			potion = "SuperPotion";
			break;
		}
		else if (c == '3') {
			potion = "HyperPotion";
			break;
		}
		else if (c == '4') {
			potion = "MaxPotion";
			break;
		}
		else {
			cout << "invalid input\n";
		}
	}

	me.usePotion(potion, pokemonName);

	// output potion info
	string s;
	s = "You used a " + potion + "!";
	coutInfo(s);
	s = pokemonName + " had its HP restored.";
	coutInfo(s);

	// random choose enemy skill
	Skill* enemySkills = enemy.getOnStagePokemon()->getAllSkills();
	string skillName = enemySkills[rand() % 4].getSkillName();

	enemyUseSkill(skillName);
	BandP();
	cinModeupdate();
}

// pass pokemon into player, and switch the pokemon on board
void Game::switchPokemon(ifstream& file) {
	// pass pokemon into player, and switch the pokemon on board
	string switchPokemonName, skillName;
	file >> switchPokemonName >> skillName;

	//output switch which pokemon
	if (me.canSwitch(switchPokemonName)) {
		//output switch pokemon
		Pokemon* currentPokemon = me.getOnStagePokemon();
		string s;
		if (!currentPokemon->getFainted())
		{
			s = me.getOnStagePokemon()->getPokemonName() + ", switch out!";
			coutInfo(s);
			s = "Come back!";
			coutInfo(s);
		}
		s = "Go! " + switchPokemonName + '!';
		coutInfo(s);

		me.switchPokemon(switchPokemonName);
	}

	enemyUseSkill(skillName);
	BandP();
	fileModeupdate();

}

/**
  * Intent :  use cin to pass pokemon into player, and switch the pokemon on board
 */
void Game::switchPokemon() {
	// pass pokemon into player, and switch the pokemon on board
	cout << "you have 3 pokemons" << endl;

	Pokemon* myPokemons = me.getAllPokemon();
	for (int i = 0; i < 3; i++) {
		cout << i + 1 << ": " << myPokemons[i].getPokemonName() << " " << to_string(myPokemons[i].getPokemonHp()) << "/" << to_string(myPokemons[i].getPokemonMaxHp()) << ", ";
	}
	cout << endl;

	cout << "input the corresponding number to switch pokemon:\n";
	char c;
	string switchPokemonName;
	while (1) {
		cin >> c;
		if (c == '1' && !myPokemons[0].getFainted()) {
			switchPokemonName = myPokemons[0].getPokemonName();
			break;
		}
		else if (c == '2' && !myPokemons[1].getFainted()) {
			switchPokemonName = myPokemons[1].getPokemonName();
			break;
		}
		else if (c == '3' && !myPokemons[2].getFainted()) {
			switchPokemonName = myPokemons[2].getPokemonName();
			break;
		}
		else {
			cout << "invalid input\n";
		}
	}

	//output switch which pokemon
	if (me.canSwitch(switchPokemonName)) {
		//output switch pokemon
		Pokemon* currentPokemon = me.getOnStagePokemon();
		string s;
		if (!currentPokemon->getFainted())
		{
			s = me.getOnStagePokemon()->getPokemonName() + ", switch out!";
			coutInfo(s);
			s = "Come back!";
			coutInfo(s);
		}
		s = "Go! " + switchPokemonName + '!';
		coutInfo(s);

		me.switchPokemon(switchPokemonName);
	}

	Skill* enemySkills = enemy.getOnStagePokemon()->getAllSkills();
	string skillName = enemySkills[rand() % 4].getSkillName();

	enemyUseSkill(skillName);
	BandP();
	cinModeupdate();

}

// Output the moves and PP of the current player's Pokémon
void Game::Status() {
	Pokemon* myPokemon = me.getOnStagePokemon(), * enemyPokemon = enemy.getOnStagePokemon();
	string s = myPokemon->getPokemonName() + " " + to_string(myPokemon->getPokemonHp()) + " " + myPokemon->getCondition() + " "
		+ enemyPokemon->getPokemonName() + " " + to_string(enemyPokemon->getPokemonHp()) + " " + enemyPokemon->getCondition();
	coutInfo(s);
}

// Output the moves and PP of the current player's Pokémon
void Game::check() {
	Pokemon* pokemon = me.getOnStagePokemon();
	Skill* skill;
	skill = pokemon->getAllSkills();

	string s = "";
	for (int i = 0; i < 4; i++) {
		s = s + skill[i].getSkillName() + " " + to_string(skill[i].getUsePP()) + " ";
	}
	coutInfo(s);
}

// use skill, for enemy (me) 
void Game::enemyUseSkill(const string& skillName) {
	Pokemon* myPokemon = me.getOnStagePokemon(), * enemyPokemon = enemy.getOnStagePokemon();
	Skill* enemySkill = enemyPokemon->getSkill(skillName);

	if (enemyPokemon->getFainted()) return;
	if (enemySkill->getUsePP() == 0) return;
	if (enemyPokemon->getCondition().find("PAR") != string::npos)
	{
		if (!testMode) {
			if (rand() % 4 == 0) {
				string s;
				s = s + enemyPokemon->getPokemonName() + " is paralyzed!";
				coutInfo(s);
				s = "It can't move!";
				coutInfo(s);
				return;
			}
		}
		else {
			string s;
			s = s + enemyPokemon->getPokemonName() + " is paralyzed!";
			coutInfo(s);
			s = "It can't move!";
			coutInfo(s);
			return;
		}
	}

	//output used skill
	string s = "";
	s = s + "The opposing " + enemy.getOnStagePokemon()->getPokemonName() + " used " + skillName + '!';
	coutInfo(s);

	//accuracy test
	if (!testMode) {
		int accuracy = enemySkill->getAccuracy();
		if (rand() % 100 + 1 > accuracy) {
			s = myPokemon->getPokemonName() + "avoided the attack!";
			coutInfo(s);

			// cost pp
			int pp = enemySkill->getUsePP();
			pp--;
			enemySkill->setUsePP(pp);

			return;
		}
	}

	// cal dmg
	int damage, level = 50;
	double power, attack, defence, critical, stab, type;
	power = enemySkill->getPower();

	if (enemySkill->getPS() == DamageCategory::Physical) {
		attack = enemyPokemon->getPokemonAtk();
		defence = myPokemon->getPokemonDef();
	}
	else {
		attack = enemyPokemon->getPokemonSpAtk();
		defence = myPokemon->getPokemonSpDef();
	}

	critical = 1;
	if (!testMode) {
		if (rand() % criticalRate == 0) {
			critical = 1.5;
			coutInfo("A critical hit!");
		}
	}

	stab = 1;
	vector<Type> types = enemyPokemon->getPokemonTypes();
	for (int i = 0; i < types.size(); i++) {
		if (types[i] == enemySkill->getType()) {
			stab = 1.5;
		}
	}

	type = 1;
	types.clear();
	types = myPokemon->getPokemonTypes();
	for (int i = 0; i < types.size(); i++) {
		type *= typeChart[int(enemySkill->getType())][int(types[i])];
	}
	//output Type effectiveness
	if (type >= 2)coutInfo("It's super effective!");
	else if (type == 0)coutInfo("It's not effective!");
	else if (type <= 0.5)coutInfo("It's not very effective...");

	int temp = (2 * level + 10) / 250.0 * power * attack / defence + 2;
	damage = temp * critical * stab * type;

	// do dmg
	int hp = myPokemon->getPokemonHp();
	hp -= damage;
	if (hp < 0) hp = 0;
	myPokemon->setPokemonHp(hp);

	//debuff
	if (myPokemon->getCondition().find(enemySkill->getCon()) == string::npos) {
		myPokemon->plusCondition(enemySkill->getCon());
		//output status
		s = "";
		if (enemySkill->getCon() == "PAR") s = s + me.getOnStagePokemon()->getPokemonName() + " is paralyzed, so it may be unable to move!";
		else if (enemySkill->getCon() == "PSN")s = s + me.getOnStagePokemon()->getPokemonName() + " was poisoned!";
		else if (enemySkill->getCon() == "BRN")s = s + me.getOnStagePokemon()->getPokemonName() + " was burned!";
		coutInfo(s);
	}

	// cost PP
	int pp = enemySkill->getUsePP();
	pp--;
	enemySkill->setUsePP(pp);

	// check fainting
	if (hp == 0) {
		myPokemon->setFainted(1);
	}
}

// use skill, for user (me)
void Game::meUseSkill(const string& skillName) {
	Pokemon* myPokemon = me.getOnStagePokemon(), * enemyPokemon = enemy.getOnStagePokemon();
	Skill* mySkill = myPokemon->getSkill(skillName);

	// exception process
	if (myPokemon->getFainted()) return;
	if (mySkill->getUsePP() == 0) return;
	if (myPokemon->getCondition().find("PAR") != string::npos)
	{
		if (!testMode) {
			if (rand() % 4 == 0) {
				string s;
				s = s + myPokemon->getPokemonName() + " is paralyzed!";
				coutInfo(s);
				s = "It can't move!";
				coutInfo(s);
				return;
			}
		}
		else {
			string s;
			s = s + myPokemon->getPokemonName() + " is paralyzed!";
			coutInfo(s);
			s = "It can't move!";
			coutInfo(s);
			return;
		}
	}

	//output used skill
	string s = "";
	s = s + me.getOnStagePokemon()->getPokemonName() + " used " + skillName + '!';
	coutInfo(s);

	//accuracy test
	if (!testMode) {
		int accuracy = mySkill->getAccuracy();
		if (rand() % 100 + 1 > accuracy) {
			s = enemyPokemon->getPokemonName() + "avoided the attack!";
			coutInfo(s);

			// cost pp
			int pp = mySkill->getUsePP();
			pp--;
			mySkill->setUsePP(pp);

			return;
		}
	}

	// cal dmg
	int damage, level = 50;
	double power, attack, defence, critical, stab, type;
	power = mySkill->getPower();

	if (mySkill->getPS() == DamageCategory::Physical) {
		attack = myPokemon->getPokemonAtk();
		defence = enemyPokemon->getPokemonDef();
	}
	else {
		attack = myPokemon->getPokemonSpAtk();
		defence = enemyPokemon->getPokemonSpDef();
	}

	critical = 1;
	if (!testMode) {
		if (rand() % criticalRate == 0) {
			critical = 1.5;
			coutInfo("A critical hit!");
		}
	}

	stab = 1;
	vector<Type> types = myPokemon->getPokemonTypes();
	for (int i = 0; i < types.size(); i++) {
		if (types[i] == mySkill->getType()) {
			stab = 1.5;
		}
	}

	type = 1;
	types.clear();
	types = enemyPokemon->getPokemonTypes();
	for (int i = 0; i < types.size(); i++) {
		type *= typeChart[int(mySkill->getType())][int(types[i])];
	}
	//output Type effectiveness
	if (type >= 2)coutInfo("It's super effective!");
	else if (type == 0)coutInfo("It's not effective!");
	else if (type <= 0.5)coutInfo("It's not very effective...");

	int temp = (2 * level + 10) / 250.0 * power * attack / defence + 2;
	damage = temp * critical * stab * type;

	// do dmg
	int hp = enemyPokemon->getPokemonHp();
	hp -= damage;
	if (hp < 0) hp = 0;
	enemyPokemon->setPokemonHp(hp);

	// debuff
	if (enemyPokemon->getCondition().find(mySkill->getCon()) == string::npos) {
		enemyPokemon->plusCondition(mySkill->getCon());
		s = "The opposing ";
		if (mySkill->getCon() == "PAR") s = s + enemy.getOnStagePokemon()->getPokemonName() + " is paralyzed, so it may be unable to move!";
		else if (mySkill->getCon() == "PSN")s = s + enemy.getOnStagePokemon()->getPokemonName() + " was poisoned!";
		else if (mySkill->getCon() == "BRN")s = s + enemy.getOnStagePokemon()->getPokemonName() + " was burned!";
		coutInfo(s);
	}

	// cost PP
	int pp = mySkill->getUsePP();
	pp--;
	mySkill->setUsePP(pp);

	// check fainting
	if (hp == 0) {
		enemyPokemon->setFainted(1);
		string s = "The opposing " + enemyPokemon->getPokemonName() + " fainted!";
		coutInfo(s);
	}
}

// Flowchart: B&P state
void Game::BandP() {
	Pokemon* myPokemon = me.getOnStagePokemon(), * enemyPokemon = enemy.getOnStagePokemon();

	// condition check
	string paralysis = "PAR", poison = "PSN", burn = "BRN";
	if (!myPokemon->getFainted()) {
		string condition = myPokemon->getCondition();
		if (condition.find(poison) != string::npos) {
			//output hurt by poison 
			string s;
			s = s + myPokemon->getPokemonName() + " is hurt by its poisoning!";
			coutInfo(s);

			int maxHp = myPokemon->getPokemonMaxHp();
			int hp = myPokemon->getPokemonHp();
			hp -= double(maxHp) / 16.0;
			if (hp < 0) hp = 0;
			myPokemon->setPokemonHp(hp);
		}
		if (condition.find(burn) != string::npos) {
			//output hurt by burn
			string s;
			s = s + myPokemon->getPokemonName() + " is hurt by its burn!";
			coutInfo(s);

			int maxHp = myPokemon->getPokemonMaxHp();
			int hp = myPokemon->getPokemonHp();
			hp -= double(maxHp) / 16.0;
			if (hp < 0) hp = 0;
			myPokemon->setPokemonHp(hp);
		}
	}

	if (!enemyPokemon->getFainted()) {
		string condition = enemyPokemon->getCondition();
		if (condition.find(paralysis) != string::npos) {
			// nothing to do
		}
		if (condition.find(poison) != string::npos) {
			//output hurt by poison 
			string s;
			s = s + "The opposing " + enemyPokemon->getPokemonName() + " is hurt by its poisoning!";
			coutInfo(s);

			int maxHp = enemyPokemon->getPokemonMaxHp();
			int hp = enemyPokemon->getPokemonHp();
			hp -= double(maxHp) / 16;
			if (hp < 0) hp = 0;
			enemyPokemon->setPokemonHp(hp);
		}
		if (condition.find(burn) != string::npos) {
			//output hurt by burn
			string s;
			s = s + "The opposing " + enemyPokemon->getPokemonName() + " is hurt by its burn!";
			coutInfo(s);

			int maxHp = enemyPokemon->getPokemonMaxHp();
			int hp = enemyPokemon->getPokemonHp();
			hp -= double(maxHp) / 16;
			if (hp < 0) hp = 0;
			enemyPokemon->setPokemonHp(hp);
		}
	}

	// check fainting
	if (myPokemon->getPokemonHp() == 0) myPokemon->setFainted(1);
	if (enemyPokemon->getPokemonHp() == 0) enemyPokemon->setFainted(1);
}

//replace on stage pokemon if it's fainted and output info
void Game::fileModeupdate() {
	Pokemon* myPokemon = me.getOnStagePokemon(), * enemyPokemon = enemy.getOnStagePokemon();

	if (myPokemon->getFainted()) {
		if (me.pokemonAllDead()) return;
		string s = me.getOnStagePokemon()->getPokemonName() + " is fainted!";
		coutInfo(s);
		me.switchNextPokemon();
		s = "Go! " + me.getOnStagePokemon()->getPokemonName() + "!";
		coutInfo(s);

	}

	if (enemyPokemon->getFainted()) {
		enemy.switchNextPokemon();
		enemyPokemon = enemy.getOnStagePokemon();
		if (!enemyPokemon->getFainted()) {
			//output switch pokemon when fainting
			Pokemon* currentPokemon = enemy.getOnStagePokemon();
			string s;
			s = s + "Go! " + " The opposing " + currentPokemon->getPokemonName() + '!';
			coutInfo(s);
		}
	}
}

//replace on stage pokemon if it's fainted and cout info
void Game::cinModeupdate() {
	Pokemon* myPokemon = me.getOnStagePokemon(), * enemyPokemon = enemy.getOnStagePokemon();

	if (myPokemon->getFainted()) {
		if (me.pokemonAllDead()) return;
		string s = me.getOnStagePokemon()->getPokemonName() + " is fainted!";
		coutInfo(s);
		cout << "choose a pokemon to battle:\n";
		Pokemon* myPokemons = me.getAllPokemon();
		for (int i = 0; i < 3; i++) {
			cout << i + 1 << ": " << myPokemons[i].getPokemonName() << " " << to_string(myPokemons[i].getPokemonHp()) << "/" << to_string(myPokemons[i].getPokemonMaxHp()) << ", ";
		}
		cout << endl;

		cout << "input the corresponding number to switch pokemon:\n";
		char c;
		string switchPokemonName;
		while (1) {
			cin >> c;
			if (c == '1' && !myPokemons[0].getFainted()) {
				switchPokemonName = myPokemons[0].getPokemonName();
				break;
			}
			else if (c == '2' && !myPokemons[1].getFainted()) {
				switchPokemonName = myPokemons[1].getPokemonName();
				break;
			}
			else if (c == '3' && !myPokemons[2].getFainted()) {
				switchPokemonName = myPokemons[2].getPokemonName();
				break;
			}
			else {
				cout << "invalid input\n";
			}
		}

		if (me.canSwitch(switchPokemonName)) {
			//output switch pokemon
			Pokemon* currentPokemon = me.getOnStagePokemon();
			string s;
			if (!currentPokemon->getFainted())
			{
				s = me.getOnStagePokemon()->getPokemonName() + ", switch out!";
				coutInfo(s);
				s = "Come back!";
				coutInfo(s);
			}
			s = "Go! " + switchPokemonName + '!';
			coutInfo(s);

			me.switchPokemon(switchPokemonName);
		}
	}

	if (enemyPokemon->getFainted()) {
		enemy.switchNextPokemon();
		enemyPokemon = enemy.getOnStagePokemon();
		if (!enemyPokemon->getFainted()) {
			//output switch pokemon when fainting
			Pokemon* currentPokemon = enemy.getOnStagePokemon();
			string s;
			s = s + "Go! " + " The opposing " + currentPokemon->getPokemonName() + '!';
			coutInfo(s);
		}
	}
}

// Flowchart: use a move
bool Game::meFirst() {
	Pokemon* myPokemon = me.getOnStagePokemon(), * enemyPokemon = enemy.getOnStagePokemon();
	int mySpeed = myPokemon->getPokemonSpeed(), enemySpeed = enemyPokemon->getPokemonSpeed();

	if (mySpeed >= enemySpeed) return true;
	else return false;
}

// gameover check
bool Game::gameover() {
	if (me.pokemonAllDead() || enemy.pokemonAllDead()) return true;
	else return false;
}