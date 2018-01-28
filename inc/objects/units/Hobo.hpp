#include "Unit.hpp"

class Hobo : public Unit{
	protected:
		virtual void init();
	public:
		Hobo(Arena* arena, int gid);
};

