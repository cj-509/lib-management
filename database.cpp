#include "database.h"


database::database(std::string username, std::string password) {
	driver = sql::mysql::get_driver_instance();
	con = driver->connect("tcp:: //127.0.0.1:3306", username, password);
	//con->setSchema(schema);
}

database::~database() {
	delete con;
}

void database::createdb(std::string& dbname) {
	sql::Statement* stmt = con->createStatement();
	stmt->execute("CREATE DATABASE IF NOT EXISTS " + dbname);

	delete stmt;
}

void database::usedb(std::string& dbname) {
	sql::Statement* stmt = con->createStatement();
	stmt->execute("USE " + dbname);

	delete stmt;
}

void database::updatedb(const std::string& tableName) {
	if(tableExits(tableName)) {
		sql::Statement* stmt = con->createStatement();
	}
}

void database::createTable(const std::string& tableName, const std::string& fields) {
	if (!tableExits(tableName)) {
		sql::Statement* stmt = con->createStatement();
		stmt->execute("CREATE TABLE " + tableName + "(" + fields + ")");

		std::cout << "Table has been created successfully" << std::endl;
		delete stmt;
	}
	else {
		std::cout << "Table " << tableName << " already exists" << std::endl;
	}
}

void database::insertIntoDb(std::string& tableName) {
	std::string name;
	

}
bool database::tableExits(const std::string& tableName) {
	sql::Statement* stmt = con->createStatement();
	sql::ResultSet* res = stmt->executeQuery("SHOW TABLES like '" + tableName + "'");
	bool exists = res->next();
	
	delete stmt;
	delete res;
}