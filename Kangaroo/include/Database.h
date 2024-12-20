#pragma once

#include <sqlite3.h>

#include <stdexcept>
using std::runtime_error;

#include "ResultSet.h"

#include <string>
using std::string;

namespace Kangaroo {

	class Database {

	private:
		sqlite3 *handle;

		Database();

	public:
		static Database& getInstance();

		Database(const Database &) = delete;
		Database& operator=(const Database &) = delete;
		~Database();

		void init(const string &dbName);

		void update(const char *sql, ...);
		ResultSet& execute(const char *sql, ...);
	};
}
