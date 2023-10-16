#include "lib.h"


//  __DATE CLASS DEFINITION__

date::date(int y, int m, int d) : year(y), month(m), day(d) {}
date::date() : year(0000), month(0), day(0) {}

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
	/*
	if (diffDay < 0) {
		diffMonth--;
		int dayInPrevMonth = getDaysInMonth(other.year, other.month);
		diffDay += dayInPrevMonth;
	}
	if (diffMonth < 0) {
		diffYear--;
		diffMonth += 12;
	}
	*/
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
book::book(std::string t, std::string a, std::string g, std::string l, std::string i, int p,  int n) : title(t), author(a), genre(g), language(l), publicationYear(p), isbn(i), numPages(n) {}

std::string book::getTitle() {
	return title;
}
std::string book::getAuthor() {
	return author;
}
std::string book::getGenre() {
	return genre;
}
std::string book::getLanguage() {
	return language;
}
std::string book::getIsbn() {
	return isbn;
}
int book::getPublicationYear() {
	return publicationYear;
}
int book::getNumPages() {
	return numPages;
}
void book::createBook() {
	std::cout << "Enter Book's name: ";
	std::getline(std::cin, title);

	std::cout << "Enter Author's name: ";
	std::getline(std::cin, author);

	std::cout << "Enter Book's genre: ";
	std::getline(std::cin, genre);

	std::cout << "Enter: Book's language: ";
	std::getline(std::cin, language);

	std::cout << "Enter Book's ISBN: ";
	std::getline(std::cin, isbn);

	std::cout << "Enter Publication Year: ";
	std::cin >> publicationYear;

	std::cout << "Enter Number of pages: ";
	std::cin >> numPages;
}

//display book
std::ostream& operator<<(std::ostream& os, book& b) {
	os << "Title: " << b.title << std::endl;
	os << "Author: " << b.author << std::endl;
	os << "Genre: " << b.genre << std::endl;
	os << "Language: " << b.language << std::endl;
	os << "ISBN: " << b.isbn << std::endl;
	os << "Published: " << b.publicationYear << std::endl;
	os <<"Pages: " << b.numPages << std::endl;
	return os;
}
