#ifndef DATABASE_H
#define DATABASE_H
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include<cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include "lib.h"
#include <typeinfo> // for type checking

class database {
	private:
		sql::mysql::MySQL_Driver* driver;
		sql::Connection* con;
	public:
		database(const string username, const string password);
		~database();

		void createdb(string& dbname);
		void usedb(string& dbname);
		void updatedb(const string& tableNmame);
		std::string createTable(const string& tableName, const string& fields);
		void insertIntoDb(string& tableName,string column, string values);
		bool tableExits(const string& tableName);
};


#endif // DATABASE_H

