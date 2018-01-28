#include <cstdio>
#include "../../../inc/abilities/passive/MagicShield.hpp"
#include "../../../inc/objects/units/Unit.hpp"

MagicShield::MagicShield(Unit* owner) : Ability(owner) {
	this->description.push_back("Magic shield blocks all incoming damage,");
	this->description.push_back("using unit's Mana                       ");
	this->type = Ability::PASSIVE_ON_DMG;
};

MagicShield::~MagicShield() {
	
};

bool MagicShield::check(){
	return rand()%10<4;
}

bool MagicShield::cast(int dmg){
	if (!this->check()) return true;
	if (this->owner->addMana(-dmg*2)){
		this->owner->setStatus("Blocked!");
		return false;
	} 
	return true;
}
