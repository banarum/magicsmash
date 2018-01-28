#include "../Ability.hpp"

class Bomb;
class Bomber : public Ability{
	protected:
		bool check();
		Bomb* bomb;
	public:
		bool cast();
		Bomber(Unit* owner);
		virtual ~Bomber();
};

