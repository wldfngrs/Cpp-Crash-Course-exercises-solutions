#include <array>
#include <cstdio>
#include "catch.hpp"

int main() {
	printf("Listing 2-9\n");
	std::array<int, 4> arr{1, 2, 3, 4};
	printf("The third element is %d.\n", arr.at(2));
	arr.at(2) = 100;
	printf("The third element is %d.\n\n", arr.at(2));
	
	printf("Listing 2-10\n");
	unsigned long maximum = 0;
	std::array<unsigned long, 5> values{ 10,50,20,40,0 };
	for (size_t i = 0; i < 5; i++) {
		if (values[i] > maximum) maximum = values[i];
	}
	printf("The maximum values is %lu\n\n", maximum);

	printf("Listing 2-11 (Lisitng 2-10 refactored)\n");
	unsigned long max = 0;
	std::array<unsigned long, 5> vals{ 10,50,20,40,0 };
	for (unsigned long value : vals) {
		if (value > max) max = value;
	}
	printf("The maximum values is %lu\n\n", max);
}