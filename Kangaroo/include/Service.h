#pragma once

/**
 * Abstract class to take as base to create Kangaroo services. 
 */
class Service {
	
	public:
		virtual void init() = 0;
		virtual void destroy() = 0;
};

