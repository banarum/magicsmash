#include <cstdlib>
#include <algorithm>
#include "../inc/objects/actobjects/ActionObject.hpp"
#include "../inc/objects/actobjects/Bonus.hpp"
#include "../inc/objects/units/Unit.hpp"
#include "../inc/utils/OutputMatrix.hpp"
#include "../inc/Arena.hpp"

Arena::Arena(){
	Bonus::count=0;
	width = 10;
	aObjOnHold = NULL;
	int out_width = 100;
	int out_height = 5;
	outputMatrix = new OutputMatrix(out_width, out_height);
}

int Arena::getWidth(){
	return width;
}

template<typename Target>
struct ObjectToTarget {
	Target* operator ()(Object* value) const {
		return dynamic_cast<Target*>(value); 
	} 
};

void Arena::addObject(Object* object){
	object->setOnField(true);
	this->objects.push_back(object);
}

void Arena::addUnit(Unit* unit, int x){
	unit->x = x;
	this->addObject(unit);
}

void Arena::removeActionObject(ActionObject* object){
	this->removeObject(object);
}

void Arena::addActionObject(ActionObject* object, int x){
	object->x = x;
	this->addObject(object);
}

void Arena::turnActionObjects(){
	for (auto object : this->objects){
		if (object->getType()==ActionObject::TYPE){
			ActionObject* aObject = ObjectToTarget<ActionObject>()(object);
			if (!aObject->is_manual){
				aObject->trigger();
			}
		}
	}
}

void Arena::turnUnits(){
	for (auto object : this->objects){
		if (object->getType()==Unit::TYPE){
			Unit* unit = ObjectToTarget<Unit>()(object);
			unit->turn();
		}
	}
}

vector<Object*> Arena::getObjectsInRange(int x, int range, int type){
	vector<Object*> objects;
	for (auto object : this->objects){
		int dist = abs(object->x - x);
		if (dist>range) continue;
		if (object->getType()==type || type==-1){
			objects.push_back(object);
		}
	}
	return objects;
}

void Arena::spawnBonus(){
	if (Bonus::count>3) return;
	Bonus* bonus = new Bonus(this, 0);
	int count=0;
	int rnd;
	while(true){
		rnd=rand()%this->width;
		if (this->getObjectsInRange(rnd, 0).size()==0){
			break;
		}
		count++;
		if (count>1000) return;
	}
	Bonus::count++;
	this->addActionObject(bonus, rnd);
}

vector<Unit*> Arena::getUnitsInRange(int x, int range){
	vector<Object*> objects = this->getObjectsInRange(x, range, Unit::TYPE);
	vector<Unit*> units(objects.size());
	transform(objects.begin(), objects.end(), units.begin(), ObjectToTarget<Unit>());
	return units;
}

vector<ActionObject*> Arena::getActionObjectsInRange(int x, int range){
	vector<Object*> objects = this->getObjectsInRange(x, range, ActionObject::TYPE);
	vector<ActionObject*> actionObjects(objects.size());
	transform(objects.begin(), objects.end(), actionObjects.begin(), ObjectToTarget<ActionObject>());
	return actionObjects;
}

void Arena::turn(){
	this->turnActionObjects();
	this->turnUnits();
	if (rand()%10<3)
		this->spawnBonus();
}

void Arena::removeObject(Object* object){
	object->setOnField(false);
	for (auto it = this->objects.begin();it != this->objects.end();it++){
		if (*it==object){
			this->objects.erase(it);
			break;
		}
	}
}

void Arena::removeUnit(Unit* unit){
	this->removeObject(unit);
}

void Arena::prerenderField(OutputMatrix* matrix, int offset_x, int offset_y){
	ColoredChar cchar;
	cchar.color = 15;
	cchar.value = '[';
	matrix->setChar(offset_x, offset_y, cchar);
	cchar.value = ']';
	matrix->setChar(width*5+1+offset_x, offset_y, cchar);
	for (int i=0;i<width;i++){
		ColoredChar cchar;
		cchar.color = 15;
		cchar.value = '.';
		matrix->setChar(5*i+3+offset_x, offset_y, cchar);
	}
}

OutputMatrix* Arena::getOutputMatrix(){
	this->outputMatrix->clear();
	int offset_x = 5;
	int offset_y = 3;
	this->prerenderField(this->outputMatrix, offset_x, offset_y);
	
	for (auto object : this->objects){
		int m_x = object->x*5+3+offset_x;
		int m_y = offset_y;
		object->render(m_x, m_y, this->outputMatrix);
	}
	return this->outputMatrix;
}

vector<Object*> Arena::getObjectsByGid(int type, int gid){
	vector<Object*> objects;
	for (auto object : this->objects){
		if (object->getGid()!=gid) continue;
		if (object->getType()==type){
			objects.push_back(object);
		}
	}
	return objects;
}

vector<Unit*> Arena::getUnitsByGid(int gid){
	vector<Object*> objects = this->getObjectsByGid(Unit::TYPE, gid);
	vector<Unit*> units(objects.size());
	transform(objects.begin(), objects.end(), units.begin(), ObjectToTarget<Unit>());
	return units;
}
