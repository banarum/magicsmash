#include <vector>
#include <string>

using namespace std;

class Unit;
class Arena;

class HeroesFactory{
	private:
		Arena* arena;
		vector<string> heroes;
	public:
		vector<string> getHeroes();
		Unit* addHero(string name, int gid);
		HeroesFactory(Arena* arena);
};

