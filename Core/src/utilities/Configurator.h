#ifndef CONFIGURATOR_H_
#define CONFIGURATOR_H_

#include <Properties.h>

/**
 * This class is used to read the game properties from a key=value file.
 */
class Configurator : public Properties {

private:
	static Configurator *singleton;

public:
	Configurator();
	virtual ~Configurator();

	static Configurator &getInstance();
	
	void init();

	string getLanguage() const;
	void setLanguage( const string& language );
	
	bool isPlayMusic() const;
	void setPlayMusic(bool playMusic);
	
	bool isPlaySounds() const;
	void setPlaySounds(bool playSounds);
	
	bool isFullScreen() const;
	void setFullScreen(bool fullScreen);
	
	bool isAnimations() const;
	void setAnimations(bool animations);	
};

#endif

