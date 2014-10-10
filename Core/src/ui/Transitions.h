#ifndef TRANSACTIONS_H_
#define TRANSACTIONS_H_

#include <Surface.h>
#include <Window.h>

class Transitions {
public:
	Transitions();
	virtual ~Transitions();
	
	/**
	 * From right to left
	 */
	static void slideRL(Window *window, Surface *newScreen);
	

	/**
	 * From bottom to top
	 */
	static void slideTB(Window *window, Surface *newScreen);

	/**
	 * From bottom to top
	 */
	static void slideBT(Window *window, Surface *newScreen);
};

#endif

