#include <random>
#include <cstdio>
#include <iostream>

int main() {
	const int passLength = 12;
	char characters[] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789";
	std::random_device rd_engine{};
	std::uniform_int_distribution dist{0,61};
	int generateNumber = 9;
	for (int i = 0; i < generateNumber; i++) {
		std::cout << " password_" << i << " : ";
		for (int j = 0; j < passLength; j++) {
			size_t index = dist(rd_engine);
			std::cout << characters[index];
		}
		std::cout << "\n";
	}
}