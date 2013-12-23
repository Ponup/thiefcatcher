#include "Player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Player::Player() {
	id = 0;
	resolved = 0;
}

Player::Player(const Player &player) {
	id = player.getID();
	name = player.getName();
	rank = player.getRank();
	resolved = player.getResolved();
}

Player Player::operator=(const Player &player) {
	id = player.getID();
	name = player.getName();
	rank = player.getRank();
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

void Player::setName(string name) {
	this->name = name;
}

string Player::getName() const {
	return name;
}

void Player::setRank(string rank) {
	this->rank = rank;
}

string Player::getRank() const {
	return rank;
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

	sprintf(text, "Player [ id: %d, name: %s, rank: %s, resolved: %d ]",
		id, name.c_str(), rank.c_str(), resolved
	);

	return text;
}

