#ifndef FIREWORKSPS_H_
#define FIREWORKSPS_H_

#include "utilities/fx/ParticleSystem.h"

class FireworksPS : public ParticleSystem {
	
private:
	Color colors[3];
	
public:
	FireworksPS();
	virtual ~FireworksPS();	
	
	void onParticleDie();
};

#endif

