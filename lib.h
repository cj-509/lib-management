#ifndef LIB_H
#define LIB_H
#include <cmath>
#include <iostream>
#include <string>


namespace userlog {
	//MySQL user loging info
	std::string username = "root";
	std::string password = "Password";
}
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
		int admissionNo();

};
/*student class: Ends here*/


class admin {
	//for administrative user purposes
};
#endif // LIB_H

