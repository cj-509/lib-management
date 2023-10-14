#include "lib.h"

int main() {
	date last(2022, 10, 1 );
	date today(1, 5, 32);

	date new_date = last + today;

	std::cout << "New date is: " << new_date << std::endl;


	book b1("The Psychology of Money", "Morgan Housel", "Finance", "English", "97885719689", 2020, 241);
	std::cout << b1 << std::endl;
	system("pause");
	return 0;
	
}
