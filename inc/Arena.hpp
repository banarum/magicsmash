#ifndef __ARENA_HPP__
#define __ARENA_HPP__

#include <vector>
#include <string>

using namespace std;

class Object;
class Unit;
class ActionObject;
class OutputMatrix;

class Arena{
	private:
		vector<Object*> objects;
		vector<Object*> getObjectsByGid(int type, int gid);
		void addObject(Object* object);
		void removeObject(Object* object);
		void prerenderField(OutputMatrix* matrix, int offset_x, int offset_y);
		void turnUnits();
		void spawnBonus();
		void turnActionObjects();
		OutputMatrix* outputMatrix;
		int width;
	public:
		vector<Object*> getObjectsInRange(int x, int range, int type=-1);
		ActionObject* aObjOnHold;
		void turn();
		void enterActionObjectAddingMode(ActionObject object);
		vector<Unit*> getUnitsInRange(int x, int range);
		vector<Unit*> getUnitsByGid(int gid);
		void removeUnit(Unit* unit);
		void addUnit(Unit* unit, int x=0);
		vector<ActionObject*> getActionObjectsInRange(int x, int range);
		vector<ActionObject*> getActionObjectsByGid(int gid);
		void removeActionObject(ActionObject* object);
		void addActionObject(ActionObject* object, int x);
		int getWidth();
		OutputMatrix* getOutputMatrix();
		Arena();
};

#endif

