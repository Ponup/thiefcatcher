#ifndef RANDOMGEN_H_
#define RANDOMGEN_H_

#include <stdlib.h>
#include <time.h>

class RandomGen {
public:
	static inline void init() { srand(time(0)); }
	
	static inline int nextInt(int min, int max) {
		return min + (int) ((float) (max-min+1) * (rand() / (RAND_MAX + 1.0)));
	}

};

#endif /*RANDOMGEN_H_*/
