#include <cstdio>
#include "../../../inc/abilities/passive/Cowardice.hpp"
#include "../../../inc/objects/units/Unit.hpp"

Cowardice::Cowardice(Unit* owner) : Ability(owner) {
	this->description.push_back("Unit can block attack,                  ");
	this->description.push_back("or receive double damage                ");
	this->description.push_back("which relate on his HP level            ");
	this->type = Ability::PASSIVE_ON_DMG;
};

Cowardice::~Cowardice() {
	
};

bool Cowardice::check(){
	return true;//rand()%11<4;
}

bool Cowardice::cast(int dmg){
	if (!this->check()) return true;
	int rnd = (rand()%this->owner->getMaxHp())*2;
	if (this->owner->getHp()>rnd){
		this->owner->setStatus("SHIT!");
		this->owner->damage(dmg*2, false);
		return false;
	}
	this->owner->setStatus("BLOCKED!");
	return false;
}
