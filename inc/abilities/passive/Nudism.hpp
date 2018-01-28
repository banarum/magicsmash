#include "../Ability.hpp"

class Nudism : public Ability{
	protected:
		bool check();
		int addedValue;
		int ttl;
	public:
		bool cast();
		Nudism(Unit* owner);
		virtual ~Nudism();
};

