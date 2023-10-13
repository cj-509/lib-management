#ifndef LIB_H
#define LIB_H
#include <iostream>

class date {
	private:
		int year;
		int month;
		int day;
	public:
		date(int, int, int);
		date();

		int getYear();
		int getMonth();
		int getDay();

		friend std::ostream& operator<<(std::ostream& os, date& d);

};
#endif // LIB_H

