#include "ActionObject.hpp"

class Arena;
class Bomb : public ActionObject{
	private:
		void renderTtl(int x, int y, OutputMatrix* targetMatrix);
	protected:
		int ttl;
	public:
		int getTtl();
		bool trigger();
		void onAdded();
		Bomb(Arena* arena, int gid);
		void render(int x, int y, OutputMatrix* targetMatrix);
		virtual ~Bomb();
};

