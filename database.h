#ifndef DATABASE_H
#define DATABASE_H
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include<cppconn/resultset.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <iostream>
#include<string>

class database {
	private:
		sql::mysql::MySQL_Driver* driver;
		sql::Connection* con;
	public:
		database(std::string username, std::string password);
		~database();

		void createdb(std::string& dbname);
		void usedb(std::string& dbname);
		void updatedb();
		void createTable(const std::string& tableName, const std::string& fields);
		void insertIntoDb();
		bool tableExits(const std::string& tableName);
};


#endif // DATABASE_H

