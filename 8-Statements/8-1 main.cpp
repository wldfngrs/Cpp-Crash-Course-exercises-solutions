#include "mainHeader.h"
#include <cstdio>

int main() {
	for (const auto i : FibonacciRange{ 5000 }) {
		printf("%d ", i);
	}
}