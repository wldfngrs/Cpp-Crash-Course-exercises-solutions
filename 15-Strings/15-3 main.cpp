#include <string>

void countVowels(std::string_view input) {
	size_t count{};
	for (auto it = input.cbegin(); it != input.cend(); it++) {
		if (*it == 'a' || *it == 'e'
			|| *it == 'i' || *it == 'o'
			|| *it == 'u') {
			count++;
		}
	}
	printf("Vowel count: %d", count);
}

int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Missing argument!\n");
		printf("Usage: hello.exe [argument]\n");
		return 0;
	}
	std::string argument;
	int index{ 1 };
	while (index < argc) {
		argument.append(argv[index]);
		argument.append(" ");
		index++;
	}
	countVowels(argument);
}