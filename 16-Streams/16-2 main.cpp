#include <iostream>
#include <string>

int main() {
	std::string input;
	char ch;
	std::cout << "Awaiting input...\n";
	std::cin >> input;
	auto stringInput = input.c_str();

	for (int i = 0; i < strlen(stringInput); i++) {
		if ((stringInput[i] > 65) && (stringInput[i] < 90)) {
			continue;
		}
		else {
			ch = std::toupper(stringInput[i]);
			std::cout << ch;
		}
	}
}