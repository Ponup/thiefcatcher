#include "Player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Player::Player() {
	id = 0;
	name = NULL;
	resolved = 0;
}

Player::Player(const Player &player) {
	id = player.getID();
	name = strdup(player.getName());
	resolved = player.getResolved();
}

Player Player::operator=(const Player &player) {
	id = player.getID();
	name = strdup(player.getName());
	resolved = player.getResolved();
	return *this;
}

Player::~Player() {
}

void Player::setID(int id) {
	this->id = id;
}

int Player::getID() const {
	return id;
}

void Player::setName(const char *name) {
	this->name = strdup(name);
}

const char *Player::getName() const {
	return strdup(name);
}

void Player::setResolved(unsigned int resolved) {
	this->resolved = resolved;
}

unsigned int Player::getResolved() const {
	return resolved;
}

const char *Player::toString() const {
	char *text = (char *)calloc(100, sizeof(char));
	if(!text) return NULL;

	sprintf(text, "Player [ id: %d, name: %s, resolved: %d ]",
		id, name, resolved
	);

	return text;
}

