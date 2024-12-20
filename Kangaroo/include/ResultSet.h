#pragma once

#include <sqlite3.h>

class ResultSet {
	
private:
	sqlite3_stmt *handle;

public:
	ResultSet( sqlite3 *dbHandle, const char *sql );
	~ResultSet();
	
	bool hasNext();
	char *getString(int column) const;
	int getInt(int column) const;
};

