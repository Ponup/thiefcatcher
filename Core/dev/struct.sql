
CREATE TABLE place (
	id INTEGER NOT NULL PRIMARY KEY,
	name VARCHAR(40) NOT NULL
);

CREATE TABLE criminal (
	id INTEGER NOT NULL PRIMARY KEY,
	name VARCHAR(40) NOT NULL,
	genre CHAR NOT NULL,
	hobby VARCHAR(40) NOT NULL,
	hair VARCHAR(40) NOT NULL,
	feature VARCHAR(100) NOT NULL
);

CREATE TABLE country (
	id INTEGER NOT NULL PRIMARY KEY,
	name VARCHAR(40) NOT NULL,
	capital VARCHAR(50) NOT NULL,
	language VARCHAR(60) NOT NULL,
	currency VARCHAR(60) NOT NULL,
	treasure VARCHAR(60) NOT NULL,
	coord_x NUMBER NOT NULL,
	coord_y NUMBER NOT NULL,
	description VARCHAR(200) NOT NULL,
	flag_desc VARCHAR(200) NOT NULL
);

CREATE TABLE country_object (
	id_country INTEGER NOT NULL PRIMARY KEY,
	name VARCHAR(60) NOT NULL
);

CREATE TABLE player_rank (
	id INTEGER NOT NULL PRIMARY KEY,
	description VARCHAR(100) NOT NULL,
	resolved INTEGER NOT NULL
);

CREATE TABLE player (
	id INTEGER NOT NULL PRIMARY KEY,
	name VARCHAR(40) NOT NULL,
	num_resolved_cases INTEGER NOT NULL
);

CREATE TABLE player_case (
	id_player INTEGER NOT NULL PRIMARY KEY,
	id_criminal INTEGER NOT NULL,
	current_position INTEGER NOT NULL
);	

CREATE TABLE player_case_flight (
	id_player INTEGER NOT NULL,
	position INTEGER NOT NULL,
	id_country INTEGER NOT NULL
);

