#include "../../../inc/abilities/active/Bomber.hpp"
#include "../../../inc/objects/actobjects/Bomb.hpp"
#include "../../../inc/objects/units/Unit.hpp"
#include "../../../inc/Arena.hpp"

Bomber::Bomber(Unit* owner) : Ability(owner) {
	this->description.push_back("Unit can place Bomb with a timer,       ");
	this->description.push_back("after time will gone, Bomb will explode ");
	this->description.push_back("with 1 point range                      ");
	this->bomb = NULL;
	this->type = Ability::ACTIVE_ON_USE;
};

Bomber::~Bomber() {
	
};

bool Bomber::check(){
	return !this->bomb || !this->bomb->isOnField();
}

bool Bomber::cast(){
	if (!this->check()) return false;
	this->bomb = new Bomb(this->owner->getArena(), this->owner->getGid());
	this->owner->getArena()->addActionObject(this->bomb, this->owner->x);
	bool result = this->bomb->move(1);
	if (!result)
		result = this->bomb->move(-1);
	if (!result){
		this->bomb->removeSelf();
		return false;
	}
	this->owner->getArena()->aObjOnHold = this->bomb;
	return true;
}
