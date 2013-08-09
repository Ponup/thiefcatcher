#!/bin/bash

if [ -e wthim.dat ]; then
	rm wthim.dat
fi

sqlite3 wthim.dat < model.sql

