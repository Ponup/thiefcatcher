#include "Configurator.h"

Configurator *Configurator::singleton;

Configurator::Configurator() {
	
}

void Configurator::init() {
	load("config.ini");
}

Configurator::~Configurator() {
}

Configurator &Configurator::getInstance() {
	if(!singleton) {
		singleton = new Configurator();
	}

	return *singleton;
}

string Configurator::getLanguage() const {
	return getProperty("Language");
}

void Configurator::setLanguage( const string& language ) {
	setProperty("Language", language);
}

bool Configurator::isPlayMusic() const {
	return getBoolProperty("PlayMusic");
}

void Configurator::setPlayMusic(bool playMusic) {
	setBoolProperty("PlayMusic", playMusic);
}

bool Configurator::isPlaySounds() const {
	return getBoolProperty("PlaySounds");
}

void Configurator::setPlaySounds(bool playSounds) {
	setBoolProperty("PlaySounds", playSounds);
}

bool Configurator::isFullScreen() const {
	return getBoolProperty("FullScreen");
}

void Configurator::setFullScreen(bool fullScreen) {
	setBoolProperty("FullScreen", fullScreen);
}

bool Configurator::isAnimations() const {
	return getBoolProperty("Animations");
}

void Configurator::setAnimations(bool animations) {
	setBoolProperty("Animations", animations);
}

