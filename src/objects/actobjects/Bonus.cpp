#include <cstdlib>
#include <string>
#include "../../../inc/objects/actobjects/Bonus.hpp"
#include "../../../inc/objects/units/Unit.hpp"
#include "../../../inc/utils/OutputMatrix.hpp"
#include "../../../inc/utils/Mask.hpp"
#include "../../../inc/Arena.hpp"
#include "../../../inc/Consts.hpp"

Bonus::Bonus(Arena* arena, int gid) : ActionObject(arena, gid, "Bonus") {
	this->skin = "o";
	this->is_loot = true;
	this->is_manual = true;
	this->group = Mask::getGroup(AOBJECT_LOOT_GROUP);
	
	this->hp = 0;
	this->mana = 0;
	this->armor = 0;
	
	int rnd = rand()%7;
	
	switch (rnd){
		case 0:
		case 1:
		case 2:
			this->name = "HP";
			this->hp+=20;
			break;
		case 3:
		case 4:
			this->name = "Mana";
			this->mana+=20;
			break;
		case 5:
		case 6:
			this->name = "Armor";
			this->armor+=10;
			break;
	}
	
}

bool Bonus::trigger(Unit* unit){
	unit->addHp(this->hp);
	unit->addArmor(this->armor);
	unit->addMana(this->mana);
	unit->setStatus("GOTCHA");
	this->removeSelf();
	Bonus::count--;
	return true;
}

Bonus::~Bonus(){
	
}

void Bonus::render(int x, int y, OutputMatrix* targetMatrix){
	ActionObject::render(x, y, targetMatrix);
}

int Bonus::count = 0;
