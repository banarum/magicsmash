#include <math.h>
#include <string>
#include "../../../inc/objects/units/Unit.hpp"
#include "../../../inc/objects/actobjects/ActionObject.hpp"
#include "../../../inc/abilities/Ability.hpp"
#include "../../../inc/utils/Mask.hpp"
#include "../../../inc/utils/OutputMatrix.hpp"
#include "../../../inc/Arena.hpp"
#include "../../../inc/Consts.hpp"

Unit::Unit(Arena* arena, int gid, string name) : Object(arena, TYPE, gid, name, "|"){
	this->group = Mask::getGroup(UNIT_GROUP);
	
	long long slide_mask = Mask::getEmptyMask();
	long long step_mask = Mask::getEmptyMask();
	Mask::addGroup(slide_mask, AOBJECT_GROUP);
	Mask::addGroup(step_mask, AOBJECT_LOOT_GROUP);
	Mask::setMaskPart(this->mask, MASK_STEP_PART, MASK_MAX_PARTS, step_mask);
	Mask::setMaskPart(this->mask, MASK_SLIDE_PART, MASK_MAX_PARTS, slide_mask);
}

Unit::~Unit(){
	
}

bool Unit::move(int delta){
	bool result = Object::move(delta);
	if (result){
		vector<ActionObject*> aobjs = this->arena->getActionObjectsInRange(this->x, 0);
		if (aobjs.size()>0){
			ActionObject* aobj = aobjs[0];
			if (aobj->is_loot){
				aobj->trigger(this);
			}
		}
	}
	return result;
}

int Unit::getHp(){
	return hp;
}

int Unit::getMana(){
	return mana;
}

int Unit::getArmor(){
	return armor;
}

int Unit::getPower(){
	return power;
}

int Unit::getRange(){
	return range;
}

int Unit::getMaxHp(){
	return max_hp;
}

int Unit::getMaxMana(){
	return max_mana;
}

int Unit::getMaxArmor(){
	return max_armor;
}

bool Unit::addHp(int hp){
	int newHp = this->hp+hp;
	if (newHp<0){
		this->hp = 0;
		return false;
	}
	if (newHp>this->max_hp)
		newHp = this->max_hp;
	this->hp=newHp;
	return true;
}

bool Unit::addMana(int mana){
	int newMana = this->mana+mana;
	if (newMana<0){
		this->mana = 0;
		return false;
	}
	this->mana=newMana;
	return true;
}

void Unit::setStatus(string status){
	this->status = status;
}

bool Unit::addArmor(int armor){
	int newArmor = this->armor+armor;
	if (newArmor<0){
		this->armor = 0;
		return false;
	}
	if (newArmor>this->max_armor)
		this->max_armor = newArmor;
	this->armor=newArmor;
	return true;
}

bool Unit::addPower(int power){
	int newPower = this->power+power;
	if (newPower<0){
		this->power = 0;
		return false;
	}
	this->power=newPower;
	return true;
}

bool Unit::addRange(int range){
	int newRange = this->range+range;
	if (newRange<0){
		this->range = 0;
		return false;
	}
	this->range=newRange;
	return true;
}

void Unit::damage(int hp, bool use_ability){
	if (use_ability && this->passiveAbility->type==Ability::PASSIVE_ON_DMG){
		if (!this->passiveAbility->cast(hp))
			return;
	}
		
	if (this->armor>0){
		if (this->armor>=hp){
			this->addArmor(-hp);
			hp=0;
		}else{
			this->addArmor(-this->armor);
			hp-=this->armor;
		}
	}
	this->addHp(-hp);
	if (this->hp<=0){
		this->die();
	}
}

void Unit::turn(){
	if (this->passiveAbility->type==Ability::PASSIVE_ON_UPDATE){
		this->passiveAbility->cast();
	}
}

bool Unit::attack(){
	vector<Unit*> units = this->arena->getUnitsInRange(this->x, this->range);
	if (units.size()==1) return false;
	Unit* target = NULL;
	int index=0;
	while (index<units.size() && units[index]->getGid()==this->gid){
		index++;
	}
	
	if (index<units.size()){
		target = units[index];
		target->damage(this->power);
	}
	return target!=NULL;
}

void Unit::init(){
	this->hp=this->max_hp;
	this->armor=this->max_armor;
	this->mana = this->max_mana;
	
	this->max_armor = 100;
	this->is_chosen = false;
}

void Unit::removeSelf(){
	this->arena->removeUnit(this);
}

Ability* Unit::getActiveAbility(){
	return this->activeAbility;
}

Ability* Unit::getPassiveAbility(){
	return this->passiveAbility;
}

string Unit::getBar(int value, int max_value, int size){
	string bar;
	bar+='[';
	int num = ((float)value/(float)max_value)*size;
	if (value>0){
		bar+='#';
		if (num<=0){
			num = 1;
		}
	}
	for (int i=1;i<num;i++){
		bar+='#';
	}
	for (int i=num;i<size;i++){
		bar+='.';
	}
	bar+=']';
	return bar;
}

void Unit::renderHpBar(int x, int y, OutputMatrix* targetMatrix){
	vector<ColoredChar> cstring = OutputMatrix::getCCharsFromString(this->getBar(this->hp, this->max_hp, 5), GIDS_COLORS[this->gid]);
	int m_x = x-cstring.size()/2;
	int m_y = y;
	targetMatrix->setChars(m_x, m_y, cstring, true);
}

void Unit::renderArmorBar(int x, int y, OutputMatrix* targetMatrix){
	vector<ColoredChar> cstring = OutputMatrix::getCCharsFromString(this->getBar(this->armor, this->max_armor, 3), GIDS_COLORS[this->gid]);
	int m_x = x-cstring.size()/2;
	int m_y = y;
	targetMatrix->setChars(m_x, m_y, cstring, true);
}

void Unit::renderSelector(int x, int y, OutputMatrix* targetMatrix){
	int m_x = x;
	int m_y = y;
	ColoredChar cchar_skin = targetMatrix->getChar(m_x, m_y);
	cchar_skin.color+=SELECTOR_OFFSET;
	targetMatrix->setChar(m_x, m_y, cchar_skin);
}

void Unit::renderStatus(int x, int y, OutputMatrix* targetMatrix){
	vector<ColoredChar> cstring = OutputMatrix::getCCharsFromString(this->status, GIDS_COLORS[this->gid]);
	int m_x = x-cstring.size()/2;
	int m_y = y;
	targetMatrix->setChars(m_x, m_y, cstring, true);
}

void Unit::render(int x, int y, OutputMatrix* targetMatrix){
	Object::render(x, y, targetMatrix);
	this->renderHpBar(x, y-2, targetMatrix);
	if (this->armor>0){
		this->renderArmorBar(x, y-3, targetMatrix);
	}
	if (this->status.size()>0){
		this->renderStatus(x, y+1, targetMatrix);
		this->status = "";
	}
	if (this->is_chosen){
		this->renderSelector(x, y, targetMatrix);
	}
}

void Unit::die(){
	removeSelf();
}

