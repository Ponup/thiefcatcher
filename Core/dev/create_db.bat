@echo off

sqlite3 game.db < struct.sql
sqlite3 game.db < data.sql

