#ifndef LIB_H
#define LIB_H
#include <cmath> // using abs function to convert negative date result
#include <iostream>
#include <string>

using std::to_string;
using std::string;
/*Date class
					for doing simple date manipulation
*/

class date {
	private:
		int year;
		int month;
		int day;
	public:
		//constructor
		date(int, int, int);
		date();

		//setter function
		int setYear(int);
		int setMonth(int);
		int setDay(int);

		//getter function
		int getYear();
		int getMonth();
		int getDay();

		string to_str() const;

		//display date object
		friend std::ostream& operator<<(std::ostream& os, date& d);

		//date operation
		date operator - (const date& other) const;
		date operator + (const date& other) const;


		//check if a year is a leap year
		bool isLeapYear(int year) const;
		
		//helper function to get the number of days in month
		int getDaysInMonth(int year, int month) const;


};
/*End of date class*/


/*Start of book class*/
class book {
	private:
		string title;
		string author;
		string genre;
		string language;
		string isbn;
		int publicationYear;
		int numPages;
	public:
		book();
		book(string, string, string, string, string, int, int);

		//getter functions
		string getTitle();
		string getAuthor();
		string getGenre();
		string getLanguage();
		string getIsbn();
		int getPublicationYear();
		int getNumPages();

		void createBook();
		void addBook();
		void updateBook();
		void issueTo(); //


		//display book
		friend std::ostream& operator<<(std::ostream& os, book& b);

};
/*End of book class*/

/*student class: beings here*/
class student{
	private:
		string name;
		string homeTown;
		date enrollmentDate;
		int id;
		char accountType;
	public:
		student();
		student(string name, string homeTown, date enrollmentDate, int id, char accountType);
		char getAccountType();
		friend std::ostream& operator<<(std::ostream& os, student& s);
		

};
/*student class: Ends here*/


/* Admin class: starts here*/
class admin {
private:
	string username;
	string password;
	char accountType;
public:
	admin();
	admin(string username, string password, char accountType);


};
#endif // LIB_H

