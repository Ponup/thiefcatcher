#include "FireworksPS.h"

#include "utilities/fx/Rocket.h"
#include "utilities/RandomGen.h"

FireworksPS::FireworksPS() {
	colors[0] = Color(240, 240, 100);
	colors[1] = Color(255, 170, 70);
	colors[2] = Color(230, 255, 70);

	for (int i = 0; i < 70; i++) {
		Rocket *particle = new Rocket(150, 200, RandomGen::nextInt(10, 80));
		particle->setColor(Color(200, 40, 100));
		particle->initialPos = Point(RandomGen::nextInt(0, 20),
				RandomGen::nextInt(400, 600));

		addParticle(particle);
	}
}

FireworksPS::~FireworksPS() {
}

void FireworksPS::onParticleDie() {
	Rocket *particle= NULL;

	if (RandomGen::nextInt(0, 1) == 0) {
		particle = new Rocket(-50, RandomGen::nextInt(20, 120), RandomGen::nextInt(10, 80));
		particle->initialPos = Point(RandomGen::nextInt(790, 800),
				RandomGen::nextInt(400, 600));
	} else {
		particle = new Rocket(50, RandomGen::nextInt(40, 120), RandomGen::nextInt(10, 80));
		particle->initialPos = Point(RandomGen::nextInt(0, 20),
				RandomGen::nextInt(400, 600));
	}

	particle->setColor(colors[RandomGen::nextInt(0, 2)]);

	addParticle(particle);
}

