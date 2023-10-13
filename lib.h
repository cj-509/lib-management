#ifndef LIB_H
#define LIB_H
#include <iostream>

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
#endif // LIB_H

