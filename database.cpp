#include "database.h"


database::database(std::string username, std::string password, std::string schema) {
	driver = sql::mysql::get_driver_instance();
	con = driver->connect("tcp:: //127.0.0.1:3306", username, password);
	con->setSchema(schema);
}

database::~database() {
	delete con;
}