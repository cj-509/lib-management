#ifndef DATABASE_H
#define DATABASE_H
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include<cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include "lib.h"
#include <typeinfo> // for type checking

class database {
	private:
		sql::Driver* driver;
		sql::Connection* con;
	public:
		database();
		database(const string host, const string username, const string password, const string schema);
		sql::Connection* getConnection();
		~database();

		void createSchema(const string& schemaName);
		void useDatabase(string& dbname);
		void updateDatabase(const string& tableNmame);
		string createTable(const string& tableName, const string& fields);
		void insertIntoDatabase(string values);
		bool tableExits(const string& tableName);
};


#endif // DATABASE_H

