#include <cstdio>
#include "../../../inc/abilities/active/Madness.hpp"
#include "../../../inc/objects/units/Unit.hpp"

Madness::Madness(Unit* owner) : Ability(owner) {
	this->description.push_back("<Use ALL unit mana>                     ");
	this->description.push_back("After use can do 4 things:              ");
	this->description.push_back("1. Double Unit HP      30%              ");
	this->description.push_back("2. Add 100 armor       30%              ");
	this->description.push_back("3. Do nothing          20%              ");
	this->description.push_back("4. Suicide             10%              ");
	this->type = Ability::ACTIVE_ON_USE;
};

Madness::~Madness() {
	
};

bool Madness::check(){
	if (this->owner->getMana()>0){
		this->owner->addMana(-this->owner->getMana());
		return true;
	}
	return false;
}

bool Madness::cast(){
	if (!this->check()) return false;
	int rnd = rand()%9;
	
	switch(rnd){
		case 0:
		case 1:
			this->owner->setStatus("WTF!");
			this->owner->addMana(this->owner->getMana()*2);
			break;
		case 2:
		case 3:
		case 4:
			this->owner->setStatus("NICE!");
			this->owner->addHp(this->owner->getHp()*2);
			break;
		case 5:
			this->owner->setStatus("FUCK!");
			this->owner->addHp(-this->owner->getHp());
			break;
		case 6:
		case 7:
		case 8:
			this->owner->setStatus("EQUIPPED!");
			this->owner->addArmor(100);
			break;
	}
	return true;
}
