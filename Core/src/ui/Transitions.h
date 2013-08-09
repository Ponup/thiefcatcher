#ifndef TRANSACTIONS_H_
#define TRANSACTIONS_H_

#include <Surface.h>

class Transitions {
public:
	Transitions();
	virtual ~Transitions();
	
	/**
	 * From right to left
	 */
	static void slideRL(Surface *window, Surface *newScreen);
	

	/**
	 * From bottom to top
	 */
	static void slideTB(Surface *window, Surface *newScreen);

	/**
	 * From bottom to top
	 */
	static void slideBT(Surface *window, Surface *newScreen);
};

#endif

