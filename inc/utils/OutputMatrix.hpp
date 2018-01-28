#ifndef __OUTPUTMATRIX_HPP__
#define __OUTPUTMATRIX_HPP__

#include <vector>
#include <string>

using namespace std;

struct ColoredChar {
	char value;
	int color;
};

class OutputMatrix{
	private:
		vector<vector<pair<char, int> > > matrix;
		int width;
		int height;
		void setMatrixElement(int x, int y, ColoredChar cchar);
		static ColoredChar getCharFromPair(pair<char, int> element);
	public:
		static vector<ColoredChar> getCCharsFromString(string str, int color);
		int getWidth();
		int getHeight();
		void clear();
		ColoredChar getChar(int x, int y);
		void setChar(int x, int y, ColoredChar cchar);
		void setChars(int sx, int y, vector<ColoredChar> cstring, bool first_free=false);
		OutputMatrix(int width, int height);
};

#endif

