#ifndef __ABILITY_HPP__
#define __ABILITY_HPP__

#include <string>
#include <vector>

using namespace std;

class Unit;
class Ability{
	protected:
		Unit* owner;
		vector<string> description;
		virtual bool check();
	public:
		int type;
		static const int PASSIVE_ON_DMG = 0;
		static const int PASSIVE_ON_UPDATE = 1;
		static const int ACTIVE_ON_USE = 2;
		static const int DEFAULT = 3;
		virtual bool cast();
		virtual bool cast(int dmg);
		vector<string> getDescription();
		Ability(Unit* owner);
		virtual ~Ability();
};

#endif

