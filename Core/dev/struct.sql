
CREATE TABLE place (
	id INTEGER NOT NULL PRIMARY KEY,
	name VARCHAR(40) NOT NULL
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

