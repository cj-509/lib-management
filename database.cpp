#include "database.h"


database::database() {}

database::database(const string host, const string username,const string password, const string schema) {
	try {
		driver = get_driver_instance();
		con = driver->connect(host, username, password);
		con->setSchema(schema);
		std::cout << "Connected successfully" << std::endl;
	}
	catch (sql::SQLException& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

sql::Connection* database::getConnection() {
	return con;
}

database::~database() {
	delete con;
}

void database::createDatabase(string& dbname) {
	sql::Statement* stmt = con->createStatement();
	stmt->execute("CREATE DATABASE IF NOT EXISTS " + dbname);

	delete stmt;
}

void database::useDatabase(string& dbname) {
	try {
		sql::Statement* stmt = con->createStatement();
		stmt->execute("USE " + dbname);

		delete stmt;
	}
	catch (sql::SQLException& e) {
		std::cerr << e.what() << std::endl;
	}
}

void database::updateDatabase(const string& tableName) {
	if(tableExits(tableName)) {
		sql::Statement* stmt = con->createStatement();
	}
}

string database::createTable(const string& tableName, const string& fields) {
	try {
		sql::Statement* stmt = con->createStatement();
		stmt->execute("CREATE TABLE IF NOT EXISTS " + tableName + " (" + fields + ");");

		delete stmt;
		return "Table has been created successfully";
		//delete stmt;
	}
	catch (sql::SQLException& e) {
		std::cerr << "Error while creating table: " << e.what() << std::endl;
	}

	return "Table " + tableName + " already exists";
}

void database::insertIntoDatabase(string values) {
	try {
		sql::Statement* stmt = con->createStatement();
		stmt->execute(values);

		delete stmt;
	}
	catch (sql::SQLException& e) {
		std::cerr << "Insertion Error: " << e.what() << std::endl;
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