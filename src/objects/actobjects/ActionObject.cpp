#include <math.h>
#include <string>
#include "../../../inc/objects/actobjects/ActionObject.hpp"
#include "../../../inc/utils/Mask.hpp"
#include "../../../inc/utils/OutputMatrix.hpp"
#include "../../../inc/Arena.hpp"
#include "../../../inc/Consts.hpp"

ActionObject::ActionObject(Arena* arena, int gid, string name) : Object(arena, TYPE, gid, name, "x"){
	this->group = Mask::getGroup(AOBJECT_GROUP);
	
	this->is_chosen = false;
	
	long long slide_mask = Mask::getEmptyMask();
	long long step_mask = Mask::getEmptyMask();
	Mask::addGroup(slide_mask, AOBJECT_GROUP);
	Mask::addGroup(slide_mask, AOBJECT_LOOT_GROUP);
	Mask::addGroup(slide_mask, UNIT_GROUP);
	Mask::setMaskPart(this->mask, MASK_STEP_PART, MASK_MAX_PARTS, step_mask);
	Mask::setMaskPart(this->mask, MASK_SLIDE_PART, MASK_MAX_PARTS, slide_mask);
}

ActionObject::~ActionObject(){
	
}

void ActionObject::onAdded(){
	
}

bool ActionObject::trigger(){
	return true;
}

bool ActionObject::trigger(Unit* unit){
	return true;
}

void ActionObject::removeSelf(){
	this->arena->removeActionObject(this);
}

void ActionObject::renderSelector(int x, int y, OutputMatrix* targetMatrix){
	int m_x = x;
	int m_y = y;
	ColoredChar cchar_skin = targetMatrix->getChar(m_x, m_y);
	cchar_skin.color+=SELECTOR_OFFSET;
	targetMatrix->setChar(m_x, m_y, cchar_skin);
}

void ActionObject::render(int x, int y, OutputMatrix* targetMatrix){
	Object::render(x, y, targetMatrix);
	if (this->is_chosen){
		this->renderSelector(x, y, targetMatrix);
	}
}

