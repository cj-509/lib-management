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

database db(username, password);
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
	cout << "Hello World \n";
	createAccount();
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
			int id = randomN();
			char account_type = 'S';
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

			student st(name, home_town, enrollment_date, id, account_type);
			//cout << st << endl;

			//create & insertion values
			string table_name = "Students";
			string student_fiels = "name VARCHAR(255) NOT NULL, home_town VARCHAR(255), enrollment_date DATE, Id PRIMARY KEY, account_type VARCHAR(1)";
			
			string values = name + ", " + home_town + ", " + enrollment_date.to_str() + ", " + to_string(id) + ", " + to_string(account_type);

			string table_error = "Table " + table_name + " already exists";
			//database db(username, password);
			string db_createtb = db.createTable(table_name, student_fiels);
			

			if (db_createtb == table_error) {
				string student_column = "name, home_town, enrollment_date, Id, account_type"; // for inserting
				db.insertIntoDb(table_name, student_column, values);
			}
		}
		catch (std::exception& e) {
			std::cerr << e.what() << endl;
		}
	}
	else if (choice == 2) {
		try {
			//admin(std::string username, std::string password, char accountType)
			string admin_name;
			string admin_username;
			string admin_password;
			date admin_dob;
			char admin_acc_type = 'A';

			cout << "Enter your name: ";
			getline(cin, admin_name);

			cout << "Enter your DOB YYYY-MM-DD \n";
			cout << "YYYY: "; int year; cin >> year;
			admin_dob.setYear(year);

			cout << "MM: "; int month; cin >> month;
			admin_dob.setMonth(month);

			cout << "DD: "; int day; cin >> day;
			admin_dob.setDay(day);

			cout << "Enter your username: ";
			getline(cin, admin_username);

			cout << "Enter your password: ";
			getline(cin, admin_password);

			admin ad(admin_name, admin_username, admin_password, admin_dob, admin_acc_type);

			string admin_tablename = "admin_users";
			string tb_error = "Table " + admin_tablename + " already exists";

			string admin_fields = "name VARCHAR(255) NOT NULL, username VARCHAR(255) NOT NULL UNIQUE, password VARCHAR(255), dob DATE, account_type VARCHAR(1)";
			string admin_values = admin_name + ", " + admin_username + ", " + admin_password + ", " + admin_dob.to_str() + to_string(admin_acc_type);

			string admin_create_db = db.createTable(admin_name, admin_fields);


			if (admin_create_db == tb_error) {
				string admin_column = "name, username, password, dob, account_type";
				db.insertIntoDb(admin_tablename, admin_fields, admin_values);
			}

		}
		catch (std::exception& ex) {
			std::cerr << ex.what() << endl;
		}
	}

}

void login();
void deleteStudent();