#include "database.h"


database::database(const string username,const string password) {
	try {
		driver = sql::mysql::get_driver_instance();
		con = driver->connect("tcp:: //127.0.0.1:3306", username, password);
		//con->setSchema(schema);
	}
	catch (sql::SQLException& e) {
		std::cerr << "Error connecting to MYSQL: " << e.what() << std::endl;
	}
}

database::~database() {
	delete con;
}

void database::createdb(string& dbname) {
	sql::Statement* stmt = con->createStatement();
	stmt->execute("CREATE DATABASE IF NOT EXISTS " + dbname);

	delete stmt;
}

void database::usedb(string& dbname) {
	sql::Statement* stmt = con->createStatement();
	stmt->execute("USE " + dbname);

	delete stmt;
}

void database::updatedb(const string& tableName) {
	if(tableExits(tableName)) {
		sql::Statement* stmt = con->createStatement();
	}
}

string database::createTable(const string& tableName, const string& fields) {
	if (!tableExits(tableName)) {
		try {
			sql::Statement* stmt = con->createStatement();
			stmt->execute("CREATE TABLE " + tableName + "(" + fields + ")");

			delete stmt;
			return "Table has been created successfully";
			//delete stmt;
		}
		catch (sql::SQLException& e) {
			std::cerr << "Error while creating table: " << e.what() << std::endl;
		}
	}
	return "Table " + tableName + " already exists";

}

void database::insertIntoDb(string& tableName, string column, string values) {
	if (tableExits(tableName)) {
		try {
			sql::Statement* stmt = con->createStatement();
			stmt->execute("INSERT INTO " + tableName + "(" + column + ")" + "VALUES " + "(" + values + ")");

			delete stmt;
		}
		catch (sql::SQLException& e) {
			std::cerr << "Insertion Error: " << e.what() << std::endl;
		}
	}
	

}
bool database::tableExits(const string& tableName) {
	try {


		sql::Statement* stmt = con->createStatement();
		sql::ResultSet* res = stmt->executeQuery("SHOW TABLES like '" + tableName + "'");
		bool exists = res->next();

		delete stmt;
		delete res;
	}
	catch (sql::SQLException& e) {
		std::cerr << "Table exist: " << e.what() << std::endl;
	}
}