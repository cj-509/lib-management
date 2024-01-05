#ifndef LIB_H
#define LIB_H
#include <cmath> // using abs function to convert negative date result
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using std::to_string;
using std::string;
using std::ostream;
/*Date class
					for doing simple date manipulation
*/

class date {
	private:
		int year;
		int month;
		int day;

		//Helper function to parse the date string
		void parseDateString(const string& dateString);
	public:
		//constructor
		date(int, int, int);
		date();
		
		//constructor from str (yyyy-mm-dd)
		date(const string& dateString);

		// Setter method for setting the date from string
		void setDateFromString(const std::string& dateString);

		//setter methods
		void setYear(int);
		void setMonth(int);
		void setDay(int);

		//getter methods
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
		date publicationDate;
		int numPages;
	public:
		book();
		book(string title, string author, string genre, string language, string isbn, date publicationDate, int numpages);

		//getter methods
		string getTitle();
		string getAuthor();
		string getGenre();
		string getLanguage();
		string getIsbn();
		//date getPublicationDate();
		int getNumPages();


		//display book
		friend ostream& operator<<(ostream& os, book& b);

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
		string getName();
		string getHomeTown();
		
		char getAccountType();
		

};
/*student class: Ends here*/


/* Admin class: starts here*/
class admin {
private:
	string name;
	string username;
	string password;
	date DOB;
	char accountType;
public:
	admin();
	admin( string name, string username, string password, date DOB, char accountType);


};
#endif // LIB_H

