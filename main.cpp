#include <cstdio>
#include <iostream>
#include <string>
#include <time.h>
#include <windows.h>
#include <vector>
#include <stdlib.h>
#include "inc/abilities/Ability.hpp"
#include "inc/objects/units/Unit.hpp"
#include "inc/Arena.hpp"
#include "inc/utils/OutputMatrix.hpp"
#include "inc/HeroesFactory.hpp"
#include "inc/Consts.hpp"
#include "inc/objects/actobjects/ActionObject.hpp"
#include "inc/utils/Mask.hpp"

Arena* arena;
HeroesFactory* factory;

int currentTurn = 2;

//Really, I had a lot of troubles with output if I made it XD
string space = "    "; //4
string kspace = space+space; // 8
string mspace = kspace+kspace; //16
string gspace = mspace+mspace; // 32

const int TURN_UNIT = 0;
const int TURN_OBJECT = 1;

int state = TURN_UNIT;

//just to make some nice colorfull UI
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//Yeah, bad practice but quick and working
void clearScreen(){
	system("cls");
}

//Yeah, Yeah, all text in code))
void printIntro(){
	cout << endl << endl << endl;
	
	cout << space << "Welcome to MagicSmash - Epic console game!" << endl;
	cout << space;
	SetConsoleTextAttribute(hConsole, GIDS_COLORS[1]);
	cout << "PLAYER1";
	SetConsoleTextAttribute(hConsole, 15);
	cout << " vs ";
	SetConsoleTextAttribute(hConsole, GIDS_COLORS[2]);
	cout << "PLAYER2";
	cout << endl;
	SetConsoleTextAttribute(hConsole, 15);
	cout << endl;
	cout << space << "PRESS ENTER TO CONTINUE...";
	getchar();
}

void printHeroesList(){
	cout << space << "Heroes: " << endl;
	vector<string> heroes = factory->getHeroes();
	for (int i=0;i<heroes.size();i++){
		string str = heroes[i];
		cout << space << "  " << i+1 << ". " << str << endl;
	}
}

void printChooseHeroes(){
	cout << endl << endl << endl << endl << endl;
	printHeroesList();
	cout << endl << endl;
	for (int i=0;i<2;i++){
		cout << space << "Choose ";
		SetConsoleTextAttribute(hConsole, GIDS_COLORS[i+1]);
		cout << "PLAYER" << i+1;
		SetConsoleTextAttribute(hConsole, 15);
		cout << " hero:" << endl;
		cout << space;
		string input;
		cin >> input;
		char chr=input[input.size()-1];
		int num = chr-48-1;
		Unit* unit = factory->addHero(factory->getHeroes()[num], i+1);
		arena->addUnit(unit, (arena->getWidth()-1)*i);
		int delta = i*2-1;
		unit->x-=delta;
	}
}

void init(){
	printIntro();
	arena = new Arena();
	factory = new HeroesFactory(arena);
	clearScreen();
	printChooseHeroes();
}

void printUnitAbilities(Unit* unit){
	cout << kspace << "Active Ability:";
	cout << gspace+" ";
	cout << "Passive Ability:" << endl;
	for (int i=0;i<unit->getActiveAbility()->getDescription().size() || i<unit->getPassiveAbility()->getDescription().size();i++){
		cout << kspace;
		if (i<unit->getActiveAbility()->getDescription().size()){
			cout << " " << unit->getActiveAbility()->getDescription()[i];
		}else{
			cout << gspace+kspace+" ";
		}
		cout << kspace;
		if (i<unit->getPassiveAbility()->getDescription().size()){
			cout << unit->getPassiveAbility()->getDescription()[i];
		}
		cout << endl; 
	}
}

void printUnitStatistics(Unit* unit){
	SetConsoleTextAttribute(hConsole, GIDS_COLORS[unit->getGid()]);
	cout << " Name:  " << unit->getName() << endl << endl;
	cout << " HP:    " << unit->getHp() << "/" << unit->getMaxHp() << endl;
	cout << " ARMOR: " << unit->getArmor() << "/" << unit->getMaxArmor() << endl;
	cout << " MANA:  " << unit->getMana() << "/" << unit->getMaxMana() << endl;
	cout << " POWER: " << unit->getPower() << endl;
	cout << " RANGE: " << unit->getRange() << endl;
	printUnitAbilities(unit);
	SetConsoleTextAttribute(hConsole, 15);
}

//Printing Output Matrix as some kind of text Canvas
void printOutputMatrix(OutputMatrix* data){
	int prev_color;
	for (int i=0;i<data->getHeight();i++){
		prev_color = 15;
		for (int j=0;j<data->getWidth();j++){
			ColoredChar cchar = data->getChar(j, i);
			if (cchar.color!=prev_color){
				SetConsoleTextAttribute(hConsole, cchar.color);
				prev_color = cchar.color;
			}
			if (cchar.value==0)
				cchar.value = '0';
			cout << cchar.value;
		}
		SetConsoleTextAttribute(hConsole, 15);
		cout << "\n";
	}
}

Unit* getNextTurnUnit(){
	if (currentTurn==1) currentTurn=2;
	else currentTurn=1;
	vector<Unit*> units = arena->getUnitsByGid(currentTurn);
	if (units.size()>0){
		return units[0];
	}
	return NULL;
}

void printTutorial(){
	cout << "  Comands:" << endl;
	cout << "  (A) -> MOVE LEFT" << endl;
	cout << "  (D) -> MOVE RIGHT" << endl;
	cout << "  (F) -> ATTACK" << endl;
	cout << "  (G) -> CAST" << endl;
}

void printObjectTutorial(){
	cout << "  Comands:" << endl;
	cout << "  (A) -> MOVE LEFT" << endl;
	cout << "  (D) -> MOVE RIGHT" << endl;
	cout << "  (F) -> PLACE" << endl;
}

void printWin(){
	clearScreen();
	printOutputMatrix(arena->getOutputMatrix());
	cout << endl;
	cout << endl;
	cout << endl;
	
	for (int i=1;i<=2;i++){
		vector<Unit*> units = arena->getUnitsByGid(i);
		if (!units.empty())
			SetConsoleTextAttribute(hConsole, GIDS_COLORS[i]);
	}
		
	
	cout << "YOU WON";
}

bool unitTurn(){
	arena->turn();
	Unit* unit = getNextTurnUnit();
	if (unit==NULL){
		return false;
	}
	unit->is_chosen = true;
	clearScreen();
	printOutputMatrix(arena->getOutputMatrix());
	cout << endl;
	cout << endl;
	cout << endl;
	printUnitStatistics(unit);
	cout << endl;
	printTutorial();
	cout << endl;
	string input;
	
	int result = false;
	
	while(!result){
		cin >> input;
		char chr=input[input.size()-1];
		switch(chr){
			case 'a':
				result = unit->move(-1);
				break;
			case 'd':
				result = unit->move(1);
				break;
			case 'f':
				result = unit->attack();
				break;
			case 'g':
				result = unit->getActiveAbility()->cast();
				break;
		}
	}
	
	if (arena->aObjOnHold!=NULL){
		state = TURN_OBJECT;
	}
	
	unit->is_chosen = false;
	
	return true;
}

bool objectTurn(){
	arena->aObjOnHold->is_chosen = true;
	clearScreen();
	printOutputMatrix(arena->getOutputMatrix());
	arena->aObjOnHold->is_chosen = false;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "Move Object" << endl << endl;
	printObjectTutorial();
	string input;
	cin >> input;
	char chr=input[input.size()-1];
	switch(chr){
		case 'a':
			arena->aObjOnHold->move(-1);
			break;
		case 'd':
			arena->aObjOnHold->move(1);
			break;
		case 'f':
			arena->aObjOnHold->onAdded();
			arena->aObjOnHold = NULL;
			state = TURN_UNIT;
			break;
	}
	return true;
}

bool turn(){
	switch(state){
		case TURN_UNIT:
			return unitTurn();
		case TURN_OBJECT:
			return objectTurn();
	}
	return true;
}

int main() {
	srand(time(NULL));
	init();
	while(true){
		bool result = turn();
		if (!result) break;
	}
	printWin();
	getchar();
	getchar();
	return 0;
}

