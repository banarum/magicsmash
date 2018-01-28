#include "../inc/objects/units/Unit.hpp"
#include "../inc/objects/units/Hobo.hpp"
#include "../inc/objects/units/Wizard.hpp"
#include "../inc/objects/units/Warrior.hpp"
#include "../inc/HeroesFactory.hpp"
#include "../inc/Arena.hpp"

HeroesFactory::HeroesFactory(Arena* arena) : arena(arena){
	this->heroes.push_back("Goblin");
	this->heroes.push_back("Wizard");
	this->heroes.push_back("Warrior");
}

vector<string> HeroesFactory::getHeroes(){
	return this->heroes;
}

Unit* HeroesFactory::addHero(string name, int gid){
	Unit* unit = NULL;
	if (name=="Goblin"){
		unit = new Hobo(this->arena, gid);
	}else if (name=="Wizard"){
		unit = new Wizard(this->arena, gid);
	}else if (name=="Warrior"){
		unit = new Warrior(this->arena, gid);
	}
	return unit;
}
