#include "../../inc/utils/Mask.hpp"

long long Mask::getEmptyMask(){
	/*
		This will be enough for: 
			- 64 groups and 2 types of collision
			- 32 groups and 3 types of collision
			- 21 groups and 4 types of collision
			- 16 groups and 5 types of collision
			- 12 groups and 6 types of collision
			- 10 groups and 7 types of collision
			- 9 groups and 8 types of collision
			- 8 groups and 9 types of collision
	*/	
	//0
	return 0b0000000000000000000000000000000000000000000000000000000000000000;
}

void Mask::fill(long long& mask, int svalue, int evalue){
	for (int i=svalue;i<MAX_BITS && i<evalue;i++)
		mask|=BIT<<i;
}

long long Mask::getGroup(int num){
	long long group = BIT;
	group<<=num;
	return group;
}

void Mask::addGroup(long long& mask, int group){
	mask|=BIT<<group;
}

void Mask::removeGroup(long long& mask, int group){
	mask&=~(BIT<<group);
}

long long Mask::getMaskPart(long long mask, int part, int max_parts){
	int offset = MAX_BITS/max_parts;
	int final_offset = offset*(part-1);
	return mask >> final_offset;
}

void Mask::setMaskPart(long long& mask, int part, int max_parts, long long inner_mask){
	int offset = MAX_BITS/max_parts;
	int final_offset = offset*(part-1);
	mask|=inner_mask<<final_offset;
}
