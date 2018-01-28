#include "../Ability.hpp"

class MagicShield : public Ability{
	protected:
		bool check();
	public:
		bool cast(int dmg);
		MagicShield(Unit* owner);
		virtual ~MagicShield();
};

