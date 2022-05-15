#include <random>
#include <cstdio>
#include <iostream>

void generatePass(int pLength, char* chars, int passNum) {
	std::random_device rd_engine{};
	std::uniform_int_distribution dist{ 0,61 };
	for (int i = 0; i < passNum; i++) {
		std::cout << " password_" << i << " : ";
		for (int j = 0; j < pLength; j++) {
			size_t index = dist(rd_engine);
			std::cout << chars[index];
		}
		std::cout << "\n";
	}
}

int main() {
	const int passLength = 12;
	char characters[] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789";
	int passwordsToGenerate = 9;
	generatePass(passLength, characters, passwordsToGenerate);
}