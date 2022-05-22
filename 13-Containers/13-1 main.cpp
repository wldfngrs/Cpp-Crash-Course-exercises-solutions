#define CATCH_CONFIG_MAIN
#include <vector>
#include <cstdio>
#include "catch.hpp"

std::vector<int> FibonacciGenerator(const size_t elementNumber) {
	std::vector<int> resultVector;
	size_t result{};
	size_t previous{};
	size_t current{ 1 };
	for (size_t i = 0; i < elementNumber; i++) {
		result = previous + current;
		resultVector.emplace_back(result);
		previous = current;
		current = result;
	}
	return resultVector;
}

TEST_CASE("vector insert and size test") {
	std::vector<unsigned long> vectors;
	printf("Vector capacity: %d\n", vectors.capacity());
	vectors.reserve(10);
	auto result = FibonacciGenerator(20);
	vectors.assign(result.begin(), result.end());
	printf("Vector capacity: %d\n", vectors.capacity());
	REQUIRE(vectors.capacity() == vectors.size());

	// Yes the 'capacity' matches the number of elements in the vector.
	// It does because vectors use dynamic memory allocation, so the initial capacity
	// increases to accomodate the number of elements 'assign'-ed to it.

	for (auto vector : vectors) {
		printf("%u ", vector);
	}
	printf("\n");
}