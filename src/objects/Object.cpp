#include <string>
#include "../../inc/objects/Object.hpp"
#include "../../inc/utils/Mask.hpp"
#include "../../inc/utils/OutputMatrix.hpp"
#include "../../inc/Arena.hpp"
#include "../../inc/Consts.hpp"

Object::Object(Arena* arena, int type, int gid, string name, string skin) : arena(arena), type(type), gid(gid), name(name), skin(skin){
	this->group = Mask::getGroup(DEFAULT_GROUP);
	mask = Mask::getEmptyMask();
}

Object::~Object(){
	
}

int Object::getGid(){
	return gid;
}

string Object::getName(){
	return name;
}

string Object::getSkin(){
	return skin;
}

Arena* Object::getArena(){
	return arena;
}

int Object::getType(){
	return type;
}

void Object::renderName(int x, int y, OutputMatrix* targetMatrix){
	vector<ColoredChar> cstring = OutputMatrix::getCCharsFromString(this->name, GIDS_COLORS[this->gid]);
	int m_x = x-cstring.size()/2;
	int m_y = y;
	targetMatrix->setChars(m_x, m_y, cstring, true);
}

bool Object::isOnField(){
	return this->onField;
}

long long Object::getMask(){
	return this->mask;
}

bool Object::move(int delta){
	if (this->x+delta<0 || this->x+delta>=this->arena->getWidth())
		return false;
	vector<Object*> objects = this->arena->getObjectsInRange(this->x+delta, 0);
	if (objects.size()>0){
		int collision_type = this->getCollisionType(objects[0]);
		switch(collision_type){
			case SLIDE_COLLISION:
				return this->move(delta+(delta/abs(delta)));
				break;
			case STEP_COLLISION:
				break;
			default:
				return false;
		}
	}
	this->x+=delta;
	return true;
}

int Object::getCollisionType(Object* obj){
	long long group = obj->getGroup();
	
	long long slide_mask = Mask::getMaskPart(this->mask, MASK_SLIDE_PART, MASK_MAX_PARTS);
	long long step_mask = Mask::getMaskPart(this->mask, MASK_STEP_PART, MASK_MAX_PARTS);
	
	if (group&slide_mask) return SLIDE_COLLISION;
	if (group&step_mask) return STEP_COLLISION;
	return STOP_COLLISION;
}

long long Object::getGroup(){
	return this->group;
}

void Object::setOnField(bool onField){
	this->onField = onField;
}

void Object::renderSkin(int x, int y, OutputMatrix* targetMatrix){
	vector<ColoredChar> cstring = OutputMatrix::getCCharsFromString(this->skin, GIDS_COLORS[this->gid]);
	int m_x = x;
	int m_y = y;
	targetMatrix->setChars(m_x, m_y, cstring, false);
}

void Object::render(int x, int y, OutputMatrix* targetMatrix){
	this->renderSkin(x, y, targetMatrix);
	this->renderName(x, y-1, targetMatrix);
}

