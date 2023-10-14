#ifndef LIB_H
#define LIB_H
#include <cmath>
#include <iostream>
using std::string;


//for doign simple date manipulation
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
		string getTitle();
		string getAuthor();
		string getGenre();
		string getLanguage();
		string getIsbn();
		int getPublicationYear();
		int getNumPages();

		//display book
		friend std::ostream& operator<<(std::ostream& os, book& b);

};
#endif // LIB_H

