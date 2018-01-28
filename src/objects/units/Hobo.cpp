#include <string>
#include "../../../inc/objects/units/Hobo.hpp"
#include "../../../inc/abilities/active/Bomber.hpp"
#include "../../../inc/abilities/passive/Cowardice.hpp"

Hobo::Hobo(Arena* arena, int gid) : Unit(arena, gid, "Goblin") {
	init();
}

void Hobo::init(){
	max_hp = 100;
	max_armor = 0;
    max_mana = 0;
	power = 20;
	range = 1;
	activeAbility = new Bomber(this);
	passiveAbility = new Cowardice(this);
	Unit::init();
}

