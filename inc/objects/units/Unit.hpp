#ifndef __UNIT_HPP__
#define __UNIT_HPP__

#include <string>
#include "../Object.hpp"

class Ability;

class Unit : public Object{
	private:
		void renderSelector(int x, int y, OutputMatrix* targetMatrix);
		void renderHpBar(int x, int y, OutputMatrix* targetMatrix);
		void renderArmorBar(int x, int y, OutputMatrix* targetMatrix);
		void renderStatus(int x, int y, OutputMatrix* targetMatrix);
	protected:
		int hp;
	    int max_hp;
	    int mana;
	    int max_mana;
	    int armor;
		int max_armor;
		int power;
		int range;
		string status;
		void die();
		virtual void init();
		Ability* passiveAbility;
		Ability* activeAbility;
	public:
		static const int TYPE = 1;
		bool is_chosen;
		virtual bool move(int delta);
		bool addHp(int hp);
		int getHp();
		void setStatus(string status);
		int getMaxHp();
		bool addMana(int mana);
		int getMana();
		int getMaxMana();
		bool addArmor(int armor);
		int getArmor();
		int getMaxArmor();
		bool addPower(int power);
		int getPower();
		bool addRange(int range);
		int getRange();
		void turn();
		void damage(int hp, bool use_ability=true);
		Ability* getActiveAbility();
		Ability* getPassiveAbility();
		void castActive();
		bool attack();
		virtual void removeSelf();
		string getBar(int value, int max_value, int size);
		virtual void render(int x, int y, OutputMatrix* targetMatrix);
		Unit(Arena* arena, int gid, string name);
		virtual ~Unit();
};

#endif
