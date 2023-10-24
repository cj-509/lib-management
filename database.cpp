#include "database.h"


database::database(string username,string password) {
	driver = sql::mysql::get_driver_instance();
	con = driver->connect("tcp:: //127.0.0.1:3306", username, password);
	//con->setSchema(schema);
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
		sql::Statement* stmt = con->createStatement();
		stmt->execute("CREATE TABLE " + tableName + "(" + fields + ")");

		delete stmt;
		return "Table has been created successfully";
		//delete stmt;
	}
	return "Table " + tableName + " already exists";

}

void database::insertIntoDb(string& tableName, string column, string values) {
	if (tableExits(tableName)) {
		sql::Statement* stmt = con->createStatement();
		stmt->execute("INSERT INTO " + tableName + "(" + column + ")" + "VALUES " + "(" + values + ")");
	}
	

}
bool database::tableExits(const string& tableName) {
	sql::Statement* stmt = con->createStatement();
	sql::ResultSet* res = stmt->executeQuery("SHOW TABLES like '" + tableName + "'");
	bool exists = res->next();
	
	delete stmt;
	delete res;
}