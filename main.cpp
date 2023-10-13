#include "lib.h"

int main() {
	date last(2022, 5, 20);
	date today(2023, 10, 13);

	date new_date = today - last;

	std::cout << "New date is: " << new_date << std::endl;
	system("pause");
	return 0;
	
}
