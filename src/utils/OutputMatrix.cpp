#include "../../inc/utils/OutputMatrix.hpp"

OutputMatrix::OutputMatrix(int width, int height) : width(width), height(height){
	for (int i=0;i<width;i++){
		vector<pair<char, int> > column(height);
		matrix.push_back(column);
	}
}

ColoredChar OutputMatrix::getCharFromPair(pair<char, int> element){
	ColoredChar cchar;
	cchar.value = element.first;
	cchar.color = element.second;
	return cchar;
}

vector<ColoredChar> OutputMatrix::getCCharsFromString(string str, int color){
	vector<ColoredChar> cchars;
	for (int i=0;i<str.size();i++){
		ColoredChar cchar;
		cchar.value = str[i];
		cchar.color = color;
		cchars.push_back(cchar);
	}
	return cchars;
}

ColoredChar OutputMatrix::getChar(int x, int y){
	vector<pair<char, int> > column = matrix[x];
	pair<char, int> element = column[y];
	return getCharFromPair(element);
}

void OutputMatrix::setMatrixElement(int x, int y, ColoredChar cchar){
	vector<pair<char, int> >* column = &matrix[x];
	pair<char, int>* element = &(*column)[y];
	element->first = cchar.value;
	element->second = cchar.color;
}

void OutputMatrix::clear(){
	for (int i=0;i<this->width;i++){
		for (int j=0;j<this->height;j++){
			ColoredChar cchar;
			cchar.color = 0;
			cchar.value = 0;
			this->setMatrixElement(i, j, cchar);
		}
	}
}

void OutputMatrix::setChars(int sx, int y, vector<ColoredChar> cstring, bool first_free){
	
	if (first_free){
		while(sx+cstring.size()<width && this->getChar(sx+cstring.size(), y).value!=0){
			sx--;
		}
		
		while(sx<width && this->getChar(sx, y).value!=0){
			sx++;
		}
	}
	
	for (int i=0;sx+i<width && i<cstring.size();i++){
		this->setChar(sx+i, y, cstring[i]);
	}
}

void OutputMatrix::setChar(int x, int y, ColoredChar cchar){
	this->setMatrixElement(x, y, cchar);
}

int OutputMatrix::getWidth(){
	return width;
}

int OutputMatrix::getHeight(){
	return height;
}
