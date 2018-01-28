#include "../Ability.hpp"

class Cowardice : public Ability{
	protected:
		bool check();
	public:
		bool cast(int dmg);
		Cowardice(Unit* owner);
		virtual ~Cowardice();
};

