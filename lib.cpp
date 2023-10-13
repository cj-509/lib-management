#include "lib.h"


//  ___date class definition___

date::date(int y, int m, int d) : year(y), month(m), day(d) {}
date::date() {}

int date::getYear() {
	return year;
}
int date::getMonth() {
	return month;
}
int date::getDay() {
	return day;
}

std::ostream& operator<<(std::ostream& os, date& d) {
	os << d.getYear() << "-" << d.getMonth() << "-" << d.getDay() << std::endl;
	return os;
}