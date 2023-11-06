#include "lib.h"
#include "database.h"
#include <cstdlib>
#include <stdexcept>
using std::cout;
using std::cin;
using std::endl;
using std::getline;
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


int main() {
	createAccount();
	//string nn = "library";
	//db.useDatabase(nn);
	//system("mysql -u root -p");

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
		date publicationYear;
		string isbn;
		int numpages;

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
		publicationYear.setYear(year);

		cout << "MM: ";
		int month; cin >> month;
		publicationYear.setMonth(month);

		cout << "DD: ";
		int day; cin >> day;
		publicationYear.setDay(day);
		
		cout << "ISBN: ";
		cin >> isbn;

		cout << "Number of Pages: ";
		cin >> numpages;
		book b();
		//(string title, string author, string genre, string language, string isbn, int publicationYear, int numpages)

		string tableName = "book"; // book
		string fields = "title VARCHAR(255) NOT NULL, author VARCHAR(255) NOT NULL, language VARCHAR(50), isbn VARCHAR(255) NOT NULL PRIMARY KEY, INT publication_year, INT num_pages NOT NULL";
		string result = db.createTable(tableName, fields);

		if (result == "Table has been created successfully" || result == "Table " + tableName + " already exists") {
			string values = "INSERT INTO " + tableName +" (title, author, laguage, isbn, publication_year, num_pages) VALUES('" + title + "','" + author + "','" + language + "','" + isbn + "','" + publicationYear.to_str() + "','" + to_string(numpages) + "')";
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what() << endl;
		}
}