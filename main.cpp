//#include "lib.h"
#include "database.h"
#include <cstdlib>
#include <stdexcept>
using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::string;

#define username "root"
#define password "password"

int randomN();

//user management
void createAccount();
void login();
void deleteStudent();


//book management
void searchBook();
void modifyBook();
void deleteBook();


int main() {
	database db("root", "Password");

	std::string dbname = "library";
	db.createdb(dbname);
	db.createTable("students", "VARCHAR name");
	/*
	date last(2022, 10, 1 );
	date today(1, 5, 32);

	date new_date = last + today;

	std::cout << "New date is: " << new_date << std::endl;


	book b1("The Psychology of Money", "Morgan Housel", "Finance", "English", "97885719689", 2020, 241);
	std::cout << b1 << std::endl;
	*/
	system("pause");
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
	if (choice == 1) {
	
		try { //using try and except to control whether the has been created already

			string name;
			string home_town;
			date enrollment_date;
			int admission_no = randomN();
			//student(std::string name, std::string homeTown, date enrollmentDate, int admissionNo, char accountType);

			cout << "Enter your Name: ";
			getline(cin, name);


			cout << "Enter your Home Town: ";
			getline(cin, home_town);


			cout << "Enter your date of enrollment YYYY-MM-DD\n";
			cout << "YYYY: "; int year; cin >> year;
			enrollment_date.setYear(year);

			cout << "Enter your date of enrollment\n";
			cout << "MM: "; int month; cin >> month;
			enrollment_date.setMonth(month);

			cout << "Enter your date of enrollment\n";
			cout << "DD: "; int day; cin >> day;
			enrollment_date.setDay(day);

			student st(name, home_town, enrollment_date, admission_no, 'S');
			cout << st << endl;

			string table_name = "Students";
			string student_fiels = " Id PRIMARY KEY, name VARCHAR(255) NOT NULL, home_town VARCHAR(255), enrollment_date DATE,  account_type VARCHAR(1)";

			string table_error = "Table " + table_name + " already exists";
			database db(username, password);
			string db_createtb = db.createTable(table_name, student_fiels);
			
			if (db_createtb == table_error) {
				//db.insertIntoDb(table_name,)
			}
		}
		catch (std::exception& e) {
			std::cerr << "Unknown exception" << endl;
		}
	}
	else if (choice == 2) {
		//admin(std::string username, std::string password, char accountType)
	
		}

}
void login();
void deleteStudent();