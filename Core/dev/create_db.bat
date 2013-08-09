@echo off

sqlite3 wthim.dat < struct.sql
sqlite3 wthim.dat < data.sql

