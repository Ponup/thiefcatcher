#!/bin/bash

dbName=game.db

rm -f $dbName
sqlite3 $dbName < struct.sql
sqlite3 $dbName < data.sql

