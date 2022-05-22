#include <set>
#include <iostream>
#include <locale>

int main(int argc, char** argv) {
	auto comparator{[](const char* a, const char* b) {
		char a_char{};
		char b_char{};
		size_t current_index{};
		while (true) {
			a_char = std::tolower(a[current_index]);
			b_char = std::tolower(b[current_index]);
			if (a_char >= 48 && a_char <= 57
				&& b_char >= 48 && b_char <= 57) {
				int a_int = atoi(a);
				int b_int = atoi(b);
				if (a_int < b_int) {
					return true;
				}
				else if (a_int > b_int) {
					return false;
				}
			}
			else if (a_char < b_char) {
				return true;
			}
			else if (a_char > b_char) {
				return false;
			}
			++current_index;
		}
	}};
	std::set<char*, decltype(comparator)> arguments(argv, argv+argc, comparator);
	for(auto argument : arguments) {
		std::cout << argument << "\n";
	}
}