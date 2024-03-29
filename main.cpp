#include "lib.h"
#include "database.h"
#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::setw;
using std::setfill;
using std::left;


#define username "root"
#define password "password"
#define schema "library"
#define host "tcp://127.0.0.1:3306"


database db(host, username, password, schema);


int randomN(); // to generate a random 7 digits id to each student

//user management
void createAccount();
string login(sql::Connection* con);
void deleteStudent(sql::Connection* con); // to delete a specific students
void viewStudents(sql::Connection* con);


//book management
void createBook();
void addBook();
void searchBook(sql::Connection* con);
void deleteBook(sql::Connection* con);
void viewBook(sql::Connection* con);
void rentBook(sql::Connection* con);


int main() {
	//createAccount();
	cout << "========================================================" << endl;
	cout << "************ WELCOME TO LIBRARY MANAGEMENT ************" << endl;
	cout << "========================================================" << endl;
	int userChoice;
	cout << "1. Login\t 2. Create account" << endl;
	cin >> userChoice;

	if (userChoice == 1) {
		string loginResult = login(db.getConnection());
	}
	else if (userChoice == 2) {
		createAccount();
	}
	else {
		cout << "Invalid Input!!" << endl;
	}
	createAccount();
	 //login(db.getConnection());
	
	//program ends here
	cout << "Press enter to exit: ";
	cin.get();
	return 0;
	

}


int randomN() {
	int length = 7; // specify the random number lenght
	int lower_bound = 0;
	int upper_bound = 9999999;

	srand((unsigned)time(NULL));
	int random_number = lower_bound + (rand() % upper_bound);

	return random_number;
}

void createAccount() {
	int choice;

	cout << "1. Student\n2. Admin" << std::endl;
	cout << "What type of account would you like to create: ";
	cin >> choice;

	std::cin.ignore(); // clear input buffer

	if (choice == 1) {

		try {

			string name;
			string home_town;
			date enrollmentDate;
			int studentId = randomN();
			char account_type = 'S';

			// getting user data
			cout << "Enter your Name: ";
			getline(cin, name);


			cout << "Enter your Home Town: ";
			getline(cin, home_town);

			cout << "Enter your enrollment  date (YYYY-MM-DD): ";
			string setdate;
			getline(cin, setdate);
			enrollmentDate.setDateFromString(setdate);


			student st(name, home_town, enrollmentDate, studentId, account_type);
			//cout << st << endl;

			//create & insertion values
			string tableName = "students";
			string student_fiels = "name VARCHAR(255) NOT NULL, home_town VARCHAR(255), enrollment_date DATE, student_id INT PRIMARY KEY, account_type VARCHAR(1)";
			string result = db.createTable(tableName, student_fiels);

			if (result == "Table has been created successfully" || result == "Table " + tableName + " already exists") {
				string values = "INSERT INTO " + tableName + " (name, home_town, enrollment_date, student_id, account_type) VALUES('" + name + "','" + home_town + "','" + enrollmentDate.to_str() + "','" + to_string(studentId) + "','" + account_type + "')";
				db.insertIntoDatabase(values);
			} else {
				std::cerr << "Table creation failed " << endl;
			}
			
		}
		catch (std::exception& e) {
			std::cerr << e.what() << endl;
		}
	}
	else if (choice == 2) {
		try {
			
			string name;
			string aUsername;
			string aPassword;
			date dob;
			char accType = 'A';

			//int year; int month; int day;
			cout << "Enter your name: ";
			getline(cin, name);
			

			cout << "Enter your DOB (YYYY-MM-DD): ";
			string setdob;
			getline(cin, setdob);
			dob.setDateFromString(setdob);

			cout << "Enter your username: ";
			cin >> aUsername;

			cout << "Enter your password: ";
			cin >> aPassword;

			admin ad(name, aUsername, aPassword, dob, accType);

			string tableName = "admin";
			
			string admin_fields = "name VARCHAR(255) NOT NULL, username VARCHAR(255) NOT NULL UNIQUE PRIMARY KEY, password VARCHAR(255), DOB DATE, account_type VARCHAR(1)";
			//string admin_values = name + ", " + aUsername + ", " + aPassword + ", " + dob.to_str() + to_string(accType);

			string result = db.createTable(tableName, admin_fields);
			
			if (result == "Table has been created successfully" || result == "Table " + tableName + " already exists") {
				string values = "INSERT INTO " + tableName + " (name, username, password, DOB, account_type) VALUES('" + name + "','" + aUsername + "','" + aPassword + "','" + dob.to_str() + "','" + string(1, accType)  + "')";
				db.insertIntoDatabase(values);
			} 

		}
		catch (std::exception& ex) {
			std::cerr << ex.what() << endl;
		}
	}
	else {
		cout << "Invalid input" << endl;
	}

}

string login(sql::Connection* con) {

	try {
		

		int choice;
		cout << "1\tLogin as a student \n2.\tLogin as an administrator: ";
		cin >> choice;
		std::cin.ignore();

		if (choice == 1) {
			const string tableName = "students";

			int studen_id;

			cout << "Enter your Student ID: ";
			cin >> studen_id;

			const string statement = "SELECT * WHERE student_id='" + to_string(studen_id) + "' AND account_type='S'";
			sql::Statement* stmt = con->createStatement();
			sql::ResultSet* res = stmt->executeQuery(statement);

			while (res->next()) {
				string type = res->getString("account_type");
				return type;
			}

			delete res;
			delete stmt;
		}
		else if (choice == 2) {
			//getting admin username and password
			string a_username; 
			string a_password;

			//const string tableName = "admin_users";
			
			cout << "username: ";
			getline(cin, a_username);

			cout << "password: ";
			getline(cin, a_password);

			const string queryStament = "SELECT * FROM admin WHERE username='" + a_username + "' AND password='" + a_password + "' AND account_type='A'";
			sql::Statement* stmt = con->createStatement();;
			sql::ResultSet* res = stmt->executeQuery(queryStament);

			while (res->next()) {
				string type = res->getString("account_type");
				
				//delete res;
				//delete stmt;
				return type;
			}
			delete res;
			delete stmt;
		} 
		
	}
	catch (sql::SQLException& e) {
		std::cerr << e.what() << endl;
	}
}
void deleteStudent(sql::Connection* con) {
	viewStudents(db.getConnection());
	
	try {
		int id;
		cout << "Student ID: ";
		cin >> id;

		const string deletequery = "DELETE FROM students WHERE student_id = " + id;

		sql::Statement* stmt = con->createStatement();
		sql::ResultSet* res = stmt->executeQuery(deletequery);

		delete res;
		delete stmt;
	}
	catch (sql::SQLException& e) {
		std::cerr << e.what() << endl;
	}
}

void viewStudents(sql::Connection* con) {
	try {
		const string queryStatement = "SELECT * FROM students";
		sql::Statement* stmt = con->createStatement();
		sql::ResultSet* res = stmt->executeQuery(queryStatement);

		//name, home_town, enrollment_date, student_id, account_type
		std::vector<string> columnNames = { "name", "home_town", "enrollment_date", "student_id", "account_type" };
		std::vector<int> columWidths(columnNames.size(), 0);

		while (res->next()) {
			for (int i = 0; i < columnNames.size(); ++i) {
				string columnValues = res->getString(columnNames[i]);
				columWidths[i] = std::max(columWidths[i], static_cast<int>(columnValues.length()));
			}
		}
		int Width = 1;
		for (size_t i = 0; i < columnNames.size(); ++i) {
			Width += columWidths[i] + 3;
		}

		//print table header
		cout << "+";
		for (size_t i = 0; i < columWidths.size(); ++i) {
			for (int j = 0; j < columWidths[i] + 2; ++j) {
				cout << "-";
			}
			cout << "+";
		}
		cout << endl;

		std::cout << "| ";
		for (size_t i = 0; i < columnNames.size(); ++i) {
			if (columnNames[i] == "account_type") {
				cout << setw(columWidths[i] + 2) << left << " " + columnNames[i] + " |";
			}
			else {
				cout << setw(columWidths[i] + 1) << left << columnNames[i] << "|";
			}

		}
		cout << endl;

		cout << "+";
		for (size_t i = 0; i < columWidths.size(); ++i) {
			for (int j = 0; j < columWidths[i] + 2; ++j) {
				cout << "-";
			}
			cout << "+";
		}
		cout << std::endl;

		// Print table data
		res->beforeFirst();  // Reset result set to the beginning

		while (res->next()) {
			cout << "| ";
			for (size_t i = 0; i < columnNames.size(); ++i) {
				string columnValue = res->getString(columnNames[i]);
				if (columnNames[i] == "account_type") {
					cout << setw(columWidths[i] + 2) << left << " " + res->getString(columnNames[i]) + " |";
				}
				else {
					cout << setw(columWidths[i] + 1) << left << res->getString(columnNames[i]) << "|";
				}
			}
			cout << endl;

			cout << "+";
			for (size_t i = 0; i < columWidths.size(); ++i) {
				for (int j = 0; j < columWidths[i] + 2; ++j) {
					cout << "-";
				}
				cout << "+";
			}
			cout << std::endl;
		}
		delete res;
		delete stmt;
	}
	catch (sql::SQLException& e) {
		std::cerr << e.what() << endl;
	}
}

void createBook() {
	try {
		string title;
		string author;
		string subject;
		string language;
		date publicationDate;
		string isbn;
		int pages;
		cout << "Enter the book's information below \n\n";
		cout << "Title: ";
		getline(cin, title);

		cout << "Author: ";
		getline(cin, author);

		cout << "Subject: ";
		getline(cin, subject);

		cout << "Language: ";
		getline(cin, language);

		cout << "Pulication year (YYYY-MM-DD): ";
		string setPubDate;
		getline(cin, setPubDate);
		publicationDate.setDateFromString(setPubDate);
		
		cout << "ISBN: ";
		cin >> isbn;

		cout << "Pages: ";
		cin >> pages;
		book b();
		//(string title, string author, string genre, string language, string isbn, int publicationDate, int numpages)

		string tableName = "books"; // books
		string fields = "title VARCHAR(255) NOT NULL, author VARCHAR(255) NOT NULL, subject VARCHAR(50), language VARCHAR(50), isbn VARCHAR(255) NOT NULL UNIQUE PRIMARY KEY, publication_date DATE, pages INT";
		string result = db.createTable(tableName, fields);

		if (result == "Table has been created successfully" || result == "Table " + tableName + " already exists") {
			//string values = "INSERT INTO " + tableName + " (title, author, genre, laguage, isbn, publication_year, num_pages) VALUES('" + title + "','" + author + "','" + "," + genre + "," + language + "','" + isbn + "','" + publicationDate.to_str() + "','" + to_string(numPages) + "')";
			string values = "INSERT INTO " + tableName + " (title, author, subject, language, isbn, publication_date, pages) VALUES('" + title + "','" + author + "','" + subject + "','" + language + "','" + isbn + "','" + publicationDate.to_str() + "','" + to_string(pages) + "')";
			db.insertIntoDatabase(values);
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what() << endl;
		}
}

void addBook() {
	try {
		string title;
		string author;
		string subject;
		string language;
		date publicationDate;
		string isbn;
		int pages;
		cout << "Enter the book's information below \n\n";
		cout << "Title: ";
		getline(cin, title);

		cout << "Author: ";
		getline(cin, author);

		cout << "Subject: ";
		getline(cin, subject);

		cout << "Language: ";
		getline(cin, language);

		cout << "Pulication year (YYYY-MM-DD)\n";
		cout << "YYYY: ";
		int year; cin >> year;
		publicationDate.setYear(year);

		cout << "MM: ";
		int month; cin >> month;
		publicationDate.setMonth(month);

		cout << "DD: ";
		int day; cin >> day;
		publicationDate.setDay(day);

		cout << "ISBN: ";
		cin >> isbn;

		cout << "Pages: ";
		cin >> pages;

		book bk(title, author, subject, language, isbn, publicationDate, pages);

		string tableName = "books";

		string insertionValues = "INSERT INTO " + tableName + " (title, author, subject, language, isbn, publication_date, pages) VALUES('" + title + "','" + author + "','" + subject + "','" + language + "','" + isbn + "','" + publicationDate.to_str() + "','" + to_string(pages) + "')";
		db.insertIntoDatabase(insertionValues);


	}
	catch (std::exception &e) {
		std::cerr << e.what() << endl;
	}
}
void searchBook(sql::Connection* con) {

	try {
		//getting user input
		string title;
		cout << "Enter book's Title: ";
		getline(cin, title);
		
		const string query = "SELECT * FROM books WHERE title = '" + title + "'";
		sql::Statement* stmt = con->createStatement();
		sql::ResultSet* res = stmt->executeQuery(query);

		std::vector<string> columnNames = { "title", "author", "subject", "language", "isbn", "publication_date", "pages" };
		std::vector<int> columnWidths(columnNames.size(), 0);

		while (res->next()) {
			for (size_t i = 0; i < columnNames.size(); ++i) {
				string columnValues = res->getString(columnNames[i]);
				columnWidths[i] = std::max(columnWidths[i], static_cast<int>(columnValues.length()));

			}
		}
		int totalWidth = 1;
		for (size_t i = 0; i < columnNames.size(); ++i) {
			totalWidth += columnWidths[i] + 3;
		}

		//print table header
		cout << "+";
		for (size_t i = 0; i < columnWidths.size(); ++i) {
			for (int j = 0; j < columnWidths[i] + 2; ++j) {
				cout << "-";
			}
			cout << "+";
		}
		cout << endl;

		std::cout << "| ";
		for (size_t i = 0; i < columnNames.size(); ++i) {
			if (columnNames[i] == "pages") {
				cout << setw(columnWidths[i] + 2) << left << " " + columnNames[i] + " |";
			}
			else {
				cout << setw(columnWidths[i] + 1) << left << columnNames[i] << "|";
			}

		}
		cout << endl;

		cout << "+";
		for (size_t i = 0; i < columnWidths.size(); ++i) {
			for (int j = 0; j < columnWidths[i] + 2; ++j) {
				cout << "-";
			}
			cout << "+";
		}
		cout << std::endl;

		// Print table data
		res->beforeFirst();  // Reset result set to the beginning

		while (res->next()) {
			cout << "| ";
			for (size_t i = 0; i < columnNames.size(); ++i) {
				string columnValue = res->getString(columnNames[i]);
				if (columnNames[i] == "pages") {
					cout << setw(columnWidths[i] + 2) << left << " " + res->getString(columnNames[i]) + " |";
				}
				else {
					cout << setw(columnWidths[i] + 1) << left << res->getString(columnNames[i]) << "|";
				}
			}
			cout << endl;

			cout << "+";
			for (size_t i = 0; i < columnWidths.size(); ++i) {
				for (int j = 0; j < columnWidths[i] + 2; ++j) {
					cout << "-";
				}
				cout << "+";
			}
			cout << std::endl;
		}
		delete res;
		delete stmt;
	}
	catch (sql::SQLException& e) {
		std::cerr << e.what() << endl;
	}
}

void deleteBook(sql::Connection* con) {
	try {
		
		viewBook(db.getConnection());
		cin.ignore(); // clear buffer input
		string books_isbn;
		cout << "Enter the Book's isbn you would like to delete: ";
		getline(cin, books_isbn);

		const string queryStmt = "DELETE FROM books WHERE isbn = " + books_isbn;
		sql::Statement* stmt = con->createStatement();
		sql::ResultSet* res = stmt->executeQuery(queryStmt);
	}
	catch (sql::SQLException& e) {
		std::cerr << e.what() << endl;
	}
}
void viewBook(sql::Connection* con) {
	try {
		const string queryStatement = "SELECT * FROM books";
		sql::Statement* stmt = con->createStatement();
		sql::ResultSet* res = stmt->executeQuery(queryStatement);

		//get column names and find the maximum with for each column
		std::vector<string> columnNames = { "title", "author", "subject", "language", "isbn", "publication_date", "pages" };
		std::vector<int> columnWidths(columnNames.size(), 0);

		while (res->next()) {
			for (size_t i = 0; i < columnNames.size(); ++i) {
				string columnValues = res->getString(columnNames[i]);
				columnWidths[i] = std::max(columnWidths[i], static_cast<int>(columnValues.length()));
				
			}
		}
		int totalWidth = 1;
		for (size_t i = 0; i < columnNames.size(); ++i) {
			totalWidth += columnWidths[i] + 3;
		}

		//print table header
		cout << "+";
		for (size_t i = 0; i < columnWidths.size(); ++i) {
			for (int j = 0; j < columnWidths[i] + 2; ++j) {
				cout << "-";
			}
			cout << "+";
		}
		cout << endl;

		std::cout << "| ";
		for (size_t i = 0; i < columnNames.size(); ++i) {
			if (columnNames[i] == "pages") {
				cout << setw(columnWidths[i] + 2) << left << " " + columnNames[i] + " |";
			}
			else {
				cout << setw(columnWidths[i] + 1) << left << columnNames[i] << "|";
			}

		}
		cout << endl;

		cout << "+";
		for (size_t i = 0; i < columnWidths.size(); ++i) {
			for (int j = 0; j < columnWidths[i] + 2; ++j) {
				cout << "-";
			}
			cout << "+";
		}
		cout << std::endl;

		// Print table data
		res->beforeFirst();  // Reset result set to the beginning

		while (res->next()) {
			cout << "| ";
			for (size_t i = 0; i < columnNames.size(); ++i) {
				string columnValue = res->getString(columnNames[i]);
				if (columnNames[i] == "pages") {
					cout << setw(columnWidths[i] +2) << left << " " + res->getString(columnNames[i]) + " |";
				}
				else {
					cout << setw(columnWidths[i] + 1) << left << res->getString(columnNames[i]) << "|";
				}
			}
			cout << endl;

			cout << "+";
			for (size_t i = 0; i < columnWidths.size(); ++i) {
				for (int j = 0; j < columnWidths[i] + 2; ++j) {
					cout << "-";
				}
				cout << "+";
			}
			cout << std::endl;
		}
		delete res;
		delete stmt;
	}
	catch (sql::SQLException& e) {
		std::cerr << e.what() << endl;
	}
}

void rentBook(sql::Connection* con) {
	try {
		int id;
		cout << "Student ID: ";
		cin >> id;

		

	}



};
