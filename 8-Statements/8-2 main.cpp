#include "mainHeader.h"
#include <cstdio>

int main() {
	printf("\n\n---PRIME NUMBERS---\n");
	for (const auto i : PrimeNumberRange{ 5000 }) {
		printf("%d ", i);
	}
}