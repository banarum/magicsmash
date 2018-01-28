#include "ActionObject.hpp"

class Arena;
class Bonus : public ActionObject{
	protected:
		int hp;
		int mana;
		int armor;
	public:
		static int count;
		bool trigger(Unit* unit);
		Bonus(Arena* arena, int gid);
		void render(int x, int y, OutputMatrix* targetMatrix);
		virtual ~Bonus();
};

