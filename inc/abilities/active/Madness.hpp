#include "../Ability.hpp"

class Madness : public Ability{
	protected:
		bool check();
	public:
		bool cast();
		Madness(Unit* owner);
		virtual ~Madness();
};

