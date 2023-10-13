#include "lib.h"


//  ___date class definition___

date::date(int y, int m, int d) : year(y), month(m), day(d) {}
date::date() : year(1970), month(1), day(1) {}

int date::getYear() {
	return year;
}
int date::getMonth() {
	return month;
}
int date::getDay() {
	return day;
}

//display date obeject definition
std::ostream& operator<<(std::ostream& os, date& d) {
	os << d.getYear() << "-" << d.getMonth() << "-" << d.getDay() << std::endl;
	return os;
}
// Calculate the difference between two dates
date date::operator-(const date& other) const {
	int diffYear = year - other.year;
	int diffMonth = month - other.month;
	int diffDay = day - other.day;

	if (diffDay < 0) {
		diffMonth--;
		int dayInPrevMonth = getDaysInMonth(other.year, other.month);
		diffDay += dayInPrevMonth;
	}
	if (diffMonth < 0) {
		diffYear--;
		diffMonth += 12;
	}
	return date(diffYear, diffMonth, diffDay);
}

//defining leap year
bool date::isLeapYear(int year) const {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

//defining days in month funcion
int date::getDaysInMonth(int year, int month) const {
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;

	case 2:
		if (isLeapYear(year))
			return 29;
		else
			return 28;
	default:
		return -1; //invalid month
	}
}