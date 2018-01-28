#ifndef __ACTIONOBJECT_HPP__
#define __ACTIONOBJECT_HPP__

#include "../Object.hpp"

class Unit;

class ActionObject : public Object{
	private:
		void renderSelector(int x, int y, OutputMatrix* targetMatrix);
	protected:
	public:
		static const int TYPE = 2;
		bool is_chosen;
		bool is_manual;
		bool is_loot;
		virtual void onAdded();
		virtual bool trigger();
		virtual bool trigger(Unit* unit);
		virtual void removeSelf();
		ActionObject(Arena* arena, int gid, string name);
		virtual void render(int x, int y, OutputMatrix* targetMatrix);
		virtual ~ActionObject();
};

#endif
