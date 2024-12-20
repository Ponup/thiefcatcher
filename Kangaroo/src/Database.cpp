#include "Database.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

namespace Kangaroo {

	Database& Database::getInstance() {
		static Database database;
		return database;
	}

	Database::Database() {
		handle = nullptr;
	}

	Database::~Database() {
		if (handle != nullptr) {
			sqlite3_close(handle);
			handle = nullptr;
		}
	}

	void Database::init(const string &dbName) {
		int rc = sqlite3_open(dbName.c_str(), &handle);
		if (rc != SQLITE_OK) {
			throw runtime_error(sqlite3_errmsg(handle));
		}
	}

	void Database::update(const char *sql, ...) {
		char query[0x100];

		va_list params;
		va_start(params, sql);
		vsprintf(query, sql, params);
		va_end(params);

		char *errorMessage = nullptr;
		int rc = sqlite3_exec(handle, query, nullptr, nullptr, &errorMessage);
		if (rc != SQLITE_OK) {
			throw runtime_error(errorMessage);
		}
	}

	ResultSet& Database::execute(const char *sql, ...) {
		char query[0x400];
		memset(query, '\0', 0x400);

		va_list params;
		va_start(params, sql);
		vsprintf(query, sql, params);
		va_end(params);

		ResultSet *rs = new ResultSet(handle, query);
		return *rs;
	}
}
