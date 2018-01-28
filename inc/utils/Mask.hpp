class Mask {
	private:
		static const long long BIT = 1;
	public:
		static const int MAX_BITS = 8*8;
		static long long getEmptyMask();
		static long long getGroup(int num);
		static void fill(long long& mask, int svalue, int evalue);
		static void addGroup(long long& mask, int group);
		static void removeGroup(long long& mask, int group);
		static long long getMaskPart(long long mask, int part, int max_parts);
		static void setMaskPart(long long& mask, int part, int max_parts, long long inner_mask);
};
