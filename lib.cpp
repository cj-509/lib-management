#include "lib.h"


//  __DATE CLASS DEFINITION__

date::date(int y, int m, int d) : year(y), month(m), day(d) {}
date::date() : year(0000), month(0), day(0) {}

//constructor from str (yyyy-mm-dd)
date::date(const string& dateString) {
	parseDateString(dateString);
}

//Helper function to parse the date string
void date::parseDateString(const string& dateString) {
	std::istringstream ss(dateString);
	char dash1, dash2; // to skip between components
	ss >> year >> dash1 >> month >> dash2 >> day;
}

// Helper function to parse the date string
void date::setDateFromString(const std::string& dateString) {
	parseDateString(dateString);
}

void date::setYear(int yyyy) {
	year = yyyy;
}
void date::setMonth(int mm) {
	month = mm;
}
void date::setDay(int dd) {
	day = dd;
}


int date::getYear() {
	return year;
}
int date::getMonth() {
	return month;
}
int date::getDay() {
	return day;
}

string date::to_str() const {
	string formattedYear = to_string(year);
	string formattedMonth = (month < 10) ? "0" + to_string(month) : to_string(month);
	string formattedDay = (day < 10) ? "0" + to_string(day) : to_string(day);
	return formattedYear + "-" + formattedMonth + "-" + formattedDay;
}


//display date obeject definition
std::ostream& operator<<(std::ostream& os, date& d) {
	string formattedYear = to_string(d.getYear());
	string formattedMonth = (d.getMonth() < 10) ? "0" + to_string(d.getMonth()) : to_string(d.getMonth());
	string formatedDay = (d.getDay() < 10) ? "0" + to_string(d.getDay()) : to_string(d.getDay());

	os << std::setfill('0') << std::setw(4) << formattedYear << '-'
		<< std::setw(2) << formattedMonth << '-'
		<< std::setw(2) << formatedDay << std::endl;
	return os;
}
// Calculate the difference between two dates
date date::operator-(const date& other) const {
	int diffYear = year - other.year;
	int diffMonth = month - other.month;
	int diffDay = day - other.day;

	return date(abs(diffYear), abs(diffMonth), abs(diffDay));
}


date date::operator+(const date& other) const {
	int newYear = year + other.year;
	int newMonth = month + other.month;
	int newDay = day + other.day;

	while (newDay > getDaysInMonth(newYear, newMonth)) {
		newDay -= getDaysInMonth(newYear, newMonth);
		++newMonth;

		if (newMonth > 12) {
			newMonth -= 12;
			++newYear;
		}
		return date(newYear, newMonth, newDay);
	}
}

//defining leap year
bool date::isLeapYear(int year) const {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

//defining days in month funcion
int date::getDaysInMonth(int year, int month) const {
	if (month == 2) {
		return isLeapYear(year) ? 29 : 28;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		return 30;
	}
	else {
		return 31;
	}
}

//__BOOK CLASS DEFINITIONst__
book::book() {}
book::book(string t, string a, string g, string l, string i, date p,  int n) : title(t), author(a), genre(g), language(l), publicationDate(p), isbn(i), numPages(n) {}

string book::getTitle() {
	return title;
}
string book::getAuthor() {
	return author;
}
string book::getGenre() {
	return genre;
}
string book::getLanguage() {
	return language;
}
string book::getIsbn() {
	return isbn;
}

int book::getNumPages() {
	return numPages;
}

//display book
ostream& operator<<(std::ostream& os, book& b) {
	os << "Title: " << b.title << std::endl;
	os << "Author: " << b.author << std::endl;
	os << "Genre: " << b.genre << std::endl;
	os << "Language: " << b.language << std::endl;
	os << "ISBN: " << b.isbn << std::endl;
	os << "Published: " << b.publicationDate << std::endl;
	os <<"Pages: " << b.numPages << std::endl;
	return os;
}


/* __STUDENT CLASS DEFINITION__*/

student::student() {};
student::student(string name, string homeTown, date enrollmentDate, int id, char accountType) : 
	name(name), homeTown(homeTown), enrollmentDate(enrollmentDate), id(id), accountType(accountType) {}

string student::getName() {
	return name;
}

string student::getHomeTown() {
	return homeTown;
}

char student::getAccountType() {
	return accountType;
}




/* __ADMIN CLASS DEFINITION__*/
admin::admin() {}
admin::admin( string name, string username, string password, date DOB, char accountType) : name(name), username(username), password(password), DOB(DOB), accountType(accountType) {}