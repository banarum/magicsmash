#include "Unit.hpp"

class Warrior : public Unit{
	protected:
		virtual void init();
	public:
		Warrior(Arena* arena, int gid);
};

