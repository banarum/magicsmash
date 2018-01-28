#include <cstdlib>
#include <string>
#include "../../../inc/objects/actobjects/Bomb.hpp"
#include "../../../inc/objects/actobjects/ActionObject.hpp"
#include "../../../inc/objects/units/Unit.hpp"
#include "../../../inc/utils/OutputMatrix.hpp"
#include "../../../inc/Arena.hpp"
#include "../../../inc/Consts.hpp"

Bomb::Bomb(Arena* arena, int gid) : ActionObject(arena, gid, "Bomb") {
	ttl = -1;
}

void Bomb::onAdded(){
	this->ttl = (1+rand()%3)*2+1;
}

int Bomb::getTtl(){
	return this->ttl;
}

bool Bomb::trigger(){
	this->ttl--;
	if (this->ttl/2<=0){
		vector<Unit*> units = this->arena->getUnitsInRange(this->x, 1);
		for (auto it = units.begin();it < units.end();it++){
			Unit* unit = *it;
			unit->damage(unit->getHp()/2);
		}
		this->removeSelf();
	}
}

Bomb::~Bomb(){
	
}

void Bomb::renderTtl(int x, int y, OutputMatrix* targetMatrix){
	vector<ColoredChar> cstring = OutputMatrix::getCCharsFromString(to_string(this->ttl/2), GIDS_COLORS[this->gid]);
	int m_x = x-cstring.size()/2;
	int m_y = y;
	targetMatrix->setChars(m_x, m_y, cstring, true);
}

void Bomb::render(int x, int y, OutputMatrix* targetMatrix){
	ActionObject::render(x, y, targetMatrix);
	if (this->ttl/2>0){
		this->renderTtl(x, y-2, targetMatrix);
	}
}
