#include <string>
#include "../../../inc/objects/units/Wizard.hpp"
#include "../../../inc/abilities/active/Madness.hpp"
#include "../../../inc/abilities/passive/MagicShield.hpp"

Wizard::Wizard(Arena* arena, int gid) : Unit(arena, gid, "Wizard") {
	init();
}

void Wizard::init(){
	max_hp = 100;
	max_armor = 0;
    max_mana = 100;
	power = 20;
	range = 2;
	activeAbility = new Madness(this);
	passiveAbility = new MagicShield(this);
	Unit::init();
}

