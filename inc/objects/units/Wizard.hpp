#include "Unit.hpp"

class Wizard : public Unit{
	protected:
		virtual void init();
	public:
		Wizard(Arena* arena, int gid);
};

