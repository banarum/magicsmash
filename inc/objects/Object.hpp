#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <string>

class Arena;
class OutputMatrix;
using namespace std;

class Object{
	private:
		void renderName(int x, int y, OutputMatrix* targetMatrix);
		void renderSkin(int x, int y, OutputMatrix* targetMatrix);
	protected:
		Arena* arena;
		string name;
		string skin;
		int gid;
		int type;
		long long mask;
		long long group;
		bool onField;
	public:
		int x;
		virtual bool move(int delta);
		string getName();
		string getSkin();
		long long getMask();
		long long getGroup();
		int getCollisionType(Object* obj);
		int getGid();
		bool isOnField();
		void setOnField(bool onField);
		int getType();
		Arena* getArena();
		virtual void render(int x, int y, OutputMatrix* targetMatrix);
		Object(Arena* arena, int type, int gid, string name, string skin);
		virtual ~Object();
};

#endif

