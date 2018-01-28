#include "../Ability.hpp"

class WarriorSpirit : public Ability{
	protected:
		bool check();
		const int MAX_ARMOR_PER_BITE = 2;
	public:
		bool cast();
		WarriorSpirit(Unit* owner);
		virtual ~WarriorSpirit();
};

