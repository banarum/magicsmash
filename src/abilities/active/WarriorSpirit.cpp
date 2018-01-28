#include <cstdio>
#include "../../../inc/abilities/active/WarriorSpirit.hpp"
#include "../../../inc/objects/units/Unit.hpp"

WarriorSpirit::WarriorSpirit(Unit* owner) : Ability(owner) {
	this->description.push_back("Unit will eat his armor (WTF?)          ");
	this->description.push_back("and increase his attack power           ");
	this->type = Ability::ACTIVE_ON_USE;
};

WarriorSpirit::~WarriorSpirit() {
	
};

bool WarriorSpirit::check(){
	return this->owner->getArmor()>MAX_ARMOR_PER_BITE;
}

bool WarriorSpirit::cast(){
	if (!this->check()) return false;
	this->owner->addArmor(-MAX_ARMOR_PER_BITE);
	this->owner->addPower(MAX_ARMOR_PER_BITE);
	return true;
}
