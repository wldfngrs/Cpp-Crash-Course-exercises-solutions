#include <cstdio>
#include <iostream>
using namespace std;

// mode function
int mode(const int* values, size_t length) {
	if (length == 0) return 0;

	int max{}; // maximum frequency at the end of each iteration in the outer for-loop
	int amount{}; // frequency of array value at the end of it's loop
	int max_index{}; // Index of maximum frequency value

	// outer for-loop
	for (size_t i = 0; i < length; i++) {
		int cursor = values[i];

		amount++;

		for (size_t j = i + 1; j < length; j++) {
			if (cursor == values[j]) {
				amount++;
			}
		}
		if (amount > max) {
			max = amount;
			max_index = i;
			amount = 0;
		}
		else if (amount < max) {
			amount = 0;
			continue;
		}
		else if (amount == max) return 0;
	}
	return values[max_index];
}

int main() {
	int test[] = { 1,1,1,2,2,2,2,4,5,1,4,4,6,6,6,6,1,1,1,6,6,6,6,5,6,6,5,5,5,5};
	size_t length = sizeof(test) / sizeof(int);
	printf("Array : ");
	for (size_t i = 0; i < length; i++) {
		printf("%d ", test[i]);
	}

	printf("\nMode is : %d", mode(test, length));
}