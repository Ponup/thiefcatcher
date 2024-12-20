#pragma once

class FrameRegulator {
	
private:
	unsigned int framePause;
	
	unsigned int referenceTime;
	
public:
	FrameRegulator(unsigned int fps_) : framePause(1000 / fps_) {}
	void setUp();
	void regulate();
};

