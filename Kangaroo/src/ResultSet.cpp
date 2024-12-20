#include "ResultSet.h"

#include <stdexcept>
using std::runtime_error;

#include <stdio.h>
#include <string.h>

ResultSet::ResultSet( sqlite3 *dbHandle, const char *sql ) {
	const char *errorMessage = nullptr;
	int rc = sqlite3_prepare_v2(dbHandle, sql, -1, &handle, &errorMessage);
	if (rc != SQLITE_OK) {
		throw runtime_error(errorMessage);
	}
}

ResultSet::~ResultSet() {
	if (handle != nullptr) {
		sqlite3_finalize(handle);
		handle = nullptr;
	}
}

bool ResultSet::hasNext() {
	return sqlite3_step(handle) != SQLITE_DONE;
}

char *ResultSet::getString(int column) const {
	return (char *)sqlite3_column_text(handle, column);
}

int ResultSet::getInt(int column) const {
	return sqlite3_column_int(handle, column);
}

