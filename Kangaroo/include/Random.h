#pragma once

#include <vector>
using std::vector;

class Random {
private:
	static bool started;

public:
	static int nextInt(int min, int max);
	static vector<int> nextVector(vector<int> list, unsigned int limit);

	static int *nextArray(vector<int> list, unsigned int limit);
	static int *nextArray(int *list, int size, unsigned int limit);
};

