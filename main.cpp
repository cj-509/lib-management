#include "lib.h"
#include "database.h"
#include <cstdlib>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::setw;
using std::setfill;
using std::left;
//using std::string;

#define username "root"
#define password "password"
#define schema "library"
#define host "tcp://127.0.0.1:3306"

database db(host, username, password, schema);


int randomN();

//user management
void createAccount();
bool login();
void deleteStudent();
void viewStudents();


//book management
void createBook();
void addBook();
void searchBook();
void modifyBook();
void deleteBook();
void viewBook(sql::Connection* con);


int main() {
	//createAccount();
	//string nn = "library";
	//db.useDatabase(nn);
	//system("mysql -u root -p");

	addBook();

	viewBook(db.getConnection());

	return 0;

}


int randomN() {
	int length = 7; // specify the random number lenght
	int lower_bound = 1111111;
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
			int id = randomN();
			char account_type = 'S';

			// getting user data
			cout << "Enter your Name: ";
			getline(cin, name);


			cout << "Enter your Home Town: ";
			getline(cin, home_town);

			cout << "Enter your enrollment  date (YYYY-MM-DD)\n";
			cout << "YYYY: "; int year; cin >> year;
			enrollmentDate.setYear(year);

			//cout << "Enter your date of enrollment\n";
			cout << "MM: "; int month; cin >> month;
			enrollmentDate.setMonth(month);

			//cout << "Enter your date of enrollment\n";
			cout << "DD: "; int day; cin >> day;
			enrollmentDate.setDay(day);



			student st(name, home_town, enrollmentDate, id, account_type);
			//cout << st << endl;

			//create & insertion values
			string tableName = "Students";
			string student_fiels = "name VARCHAR(255) NOT NULL, home_town VARCHAR(255), enrollment_date DATE, Id INT PRIMARY KEY, account_type VARCHAR(1)";
			string result = db.createTable(tableName, student_fiels);

			if (result == "Table has been created successfully" || result == "Table " + tableName + " already exists") {
				string values = "INSERT INTO " + tableName + " (name, home_town, enrollment_date, Id, account_type) VALUES('" + name + "','" + home_town + "','" + enrollmentDate.to_str() + "','" + to_string(id) + "','" + account_type + "')";
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

			int year; int month; int day;
			cout << "Enter your name: ";
			getline(cin, name);
			

			cout << "Enter your DOB (YYYY-MM-DD) \n";
			cout << "YYYY: "; cin >> year;
			dob.setYear(year);

			cout << "MM: "; cin >> month;
			dob.setMonth(month);

			cout << "DD: "; cin >> day;
			dob.setDay(day);

			cout << "Enter your username: ";
			cin >> aUsername;

			cout << "Enter your password: ";
			cin >> aPassword;

			admin ad(name, aUsername, aPassword, dob, accType);

			string tableName = "admin_users";
			
			string admin_fields = "name VARCHAR(255) NOT NULL, username VARCHAR(255) NOT NULL UNIQUE PRIMARY KEY, password VARCHAR(255), DOB DATE, account_type VARCHAR(1)";
			//string admin_values = name + ", " + aUsername + ", " + aPassword + ", " + dob.to_str() + to_string(accType);

			string result = db.createTable(name, admin_fields);


			if (result == "Table has been created successfully" || result == "Table " + tableName + " already exists") {
				string values = "INSERT INTO " + tableName + " (name, username, password, DOB, account_type) VALUES('" + name + "','" + aUsername + "','" + aPassword + "','" + dob.to_str() + "','" + accType  + "')";
				db.insertIntoDatabase(values);
			}

		}
		catch (std::exception& ex) {
			std::cerr << ex.what() << endl;
		}
	}

}

bool login();
void deleteStudent();
void viewStudents();

void createBook() {
	try {
		string title;
		string author;
		string genre;
		string language;
		date publicationDate;
		string isbn;
		int pages;
		cout << "Enter the book's information below \n\n";
		cout << "Title: ";
		getline(cin, title);

		cout << "Author: ";
		getline(cin, author);

		cout << "Genre: ";
		getline(cin, genre);

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
		book b();
		//(string title, string author, string genre, string language, string isbn, int publicationDate, int numpages)

		string tableName = "books"; // books
		string fields = "title VARCHAR(255) NOT NULL, author VARCHAR(255) NOT NULL, genre VARCHAR(50), language VARCHAR(50), isbn VARCHAR(255) NOT NULL, publication_date DATE, pages INT";
		string result = db.createTable(tableName, fields);

		if (result == "Table has been created successfully" || result == "Table " + tableName + " already exists") {
			//string values = "INSERT INTO " + tableName + " (title, author, genre, laguage, isbn, publication_year, num_pages) VALUES('" + title + "','" + author + "','" + "," + genre + "," + language + "','" + isbn + "','" + publicationDate.to_str() + "','" + to_string(numPages) + "')";
			string values = "INSERT INTO " + tableName + " (title, author, genre, language, isbn, publication_date, pages) VALUES('" + title + "','" + author + "','" + genre + "','" + language + "','" + isbn + "','" + publicationDate.to_str() + "','" + to_string(pages) + "')";
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
		string genre;
		string language;
		date publicationDate;
		string isbn;
		int pages;
		cout << "Enter the book's information below \n\n";
		cout << "Title: ";
		getline(cin, title);

		cout << "Author: ";
		getline(cin, author);

		cout << "Genre: ";
		getline(cin, genre);

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

		book bk(title, author, genre, language, isbn, publicationDate, pages);

		string tableName = "books";

		string insertionValues = "INSERT INTO " + tableName + " (title, author, genre, language, isbn, publication_date, pages) VALUES('" + title + "','" + author + "','" + genre + "','" + language + "','" + isbn + "','" + publicationDate.to_str() + "','" + to_string(pages) + "')";
		db.insertIntoDatabase(insertionValues);


	}
	catch (std::exception &e) {
		std::cerr << e.what() << endl;
	}
}


void viewBook(sql::Connection* con) {
	try {
		const string queryStatement = "SELECT * FROM books";
		sql::Statement* stmt = con->createStatement();
		sql::ResultSet* res = stmt->executeQuery(queryStatement);

		//get column names and find the maximum with for each column
		std::vector<std::string> columnNames = { "title", "author", "genre", "language", "isbn", "publication_date", "pages" };
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
	}
	catch (sql::SQLException& e) {
		std::cerr << e.what() << endl;
	}
}
