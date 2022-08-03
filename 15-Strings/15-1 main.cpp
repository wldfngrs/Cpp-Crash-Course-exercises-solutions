#include <cstdio>
#include <cstdint>
#include <string>
#include <iostream>
#include <map>
#include <unordered_map>

constexpr char pos_A{ 65 }, pos_Z{ 90 }, pos_a{ 97 }, pos_z{ 122 };
constexpr bool within_AZ(char x) {
	return pos_A <= x && pos_Z >= x;
}
constexpr bool within_az(char x) {
	return pos_a <= x && pos_z >= x;
}

struct AlphaHistogram {
	void ingest(std::string_view x);
	void print() const;
private:
	std::unordered_map<char, int> counts;
};

void AlphaHistogram::ingest(std::string_view x) {
	for (auto letter : x) {
		if (within_AZ(letter)) {
			counts[letter]++;
		}
		else if (within_az(letter)) {
			counts[letter]++;
		}
	}
}

void AlphaHistogram::print() const {
	/*for (auto it = counts.cbegin(); it != counts.cend(); it++) {
		std::cout << it->first << ": ";
		auto elementCount = it->second;
		while (elementCount--) printf("*");
		printf("\n");
	}*/
	size_t n_astericks;
	for (auto index{ pos_A }; index <= pos_Z; index++) {
		printf("%c: ", index);
		char alphabet = index;
		try {
			counts.at(std::tolower(alphabet));
		}
		catch (const std::exception& e) {
			printf("\n");
			continue;
		}
		auto n_astericks = counts.at(std::tolower(alphabet));
		while (n_astericks--) printf("*");
		printf("\n");
	}
}

int main(int argc, char** argv) {
	AlphaHistogram hist;
	std::string input;
	int index{ 1 };
	while (index < argc) {
		input.append(argv[index]);
		input.append(" ");
		index++;
	}
	hist.ingest(input);
	hist.print();
}
