#ifndef LIB_H
#define LIB_H
#include <cmath> // using abs function to convert negative date result
#include <iostream>
#include <string>

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
		std::string title;
		std::string author;
		std::string genre;
		std::string language;
		std::string isbn;
		int publicationYear;
		int numPages;
	public:
		book();
		book(std::string, std::string, std::string, std::string, std::string, int, int);

		//getter functions
		std::string getTitle();
		std::string getAuthor();
		std::string getGenre();
		std::string getLanguage();
		std::string getIsbn();
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
		std::string name;
		std::string homeTown;
		date enrollmentDate;
		int admissionNo;
		char accountType;
	public:
		student();
		student(std::string name, std::string homeTown, date enrollmentDate, int admissionNo, char accountType);
		char getAccountType();
		friend std::ostream& operator<<(std::ostream& os, student& s);
		

};
/*student class: Ends here*/


/* Admin class: starts here*/
class admin {
private:
	std::string username;
	std::string password;
	char accountType;
public:
	admin();
	admin(std::string username, std::string password, char accountType);


};
#endif // LIB_H

