#include "../../inc/abilities/Ability.hpp"
#include "../../inc/objects/units/Unit.hpp"

Ability::Ability(Unit* owner) {
	this->owner=owner;
	this->type = Ability::DEFAULT;
};

Ability::~Ability() {
	
};

bool Ability::check(){
	
}

bool Ability::cast(){
	
}

vector<string> Ability::getDescription(){
	return description;
}

bool Ability::cast(int dmg){
	
}
