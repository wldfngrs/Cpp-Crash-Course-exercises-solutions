#include <cstdio>
#include <cstdint>
#include <string>
#include <iostream>

void isPalindrome(std::string_view testString) {
	auto begin = std::make_reverse_iterator(testString.cend());
	auto end = std::make_reverse_iterator(testString.cbegin());
	std::string inputCopy(begin, end);
	if (testString == inputCopy) {
		std::cout << "'" << testString << "' is a palindrome\n";
	}
	else {
		std::cout << "'" << testString << "' is not a palindrome\n";
	}
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Missing argument!\n");
		printf("Usage: hello.exe [argument]\n");
		return 0;
	}
	std::string input;
	int index{1};
	while (index < argc) {
		input.append(argv[index]);
		index++;
	}

	isPalindrome(input);
}
