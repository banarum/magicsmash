#include "../../../inc/abilities/passive/Nudism.hpp"
#include "../../../inc/objects/units/Unit.hpp"

Nudism::Nudism(Unit* owner) : Ability(owner) {
	this->description.push_back("Double Unit power when no Armor        ");
	this->description.push_back("during next 3 turns                    ");
	this->type = Ability::PASSIVE_ON_UPDATE;
	this->addedValue=0;
	this->ttl = 3;
};

Nudism::~Nudism() {
	
};

bool Nudism::check(){
	if (this->owner->getArmor()>0){
		this->ttl=6;
		return false;
	}else if (this->ttl>0){
		this->ttl--;
		return true;
	}
	return false;
}

bool Nudism::cast(){
	this->owner->addPower(-this->addedValue);
	this->addedValue=0;
	if (!this->check()){
		return false;
	}
	this->ttl--;
	int value = this->owner->getPower();
	this->owner->addPower(value);
	this->addedValue = value;
	this->owner->setStatus("BUFF!");
	return true;
}
