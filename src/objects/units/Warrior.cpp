#include <string>
#include "../../../inc/objects/units/Warrior.hpp"
#include "../../../inc/abilities/active/WarriorSpirit.hpp"
#include "../../../inc/abilities/passive/Nudism.hpp"

Warrior::Warrior(Arena* arena, int gid) : Unit(arena, gid, "Warrior") {
	init();
}

void Warrior::init(){
	max_hp = 100;
	max_armor = 40;
    max_mana = 0;
	power = 20;
	range = 1;
	activeAbility = new WarriorSpirit(this);
	passiveAbility = new Nudism(this);
	Unit::init();
}

