#include <cstdio>
#include <cstddef>
#include <type_traits>

template <typename T>
requires std::is_integral<T>::value
T mode(const T* values, size_t length) {
	if (length == 0) return 0;

	int max{}; // maximum frequency at the end of each iteration in the outer for-loop
	int amount{}; // frequency of array value at the end of it's loop
	int max_index{}; // Index of maximum frequency value

	// outer for-loop
	for (size_t i = 0; i < length; i++) {
		T cursor = values[i];

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
	double test[] = { 1.0,2.5,3.6};
	size_t length = sizeof(test) / sizeof(double);
	printf("Array : ");
	for (size_t i = 0; i < length; i++) {
		printf("%f ", test[i]);
	}

	printf("\nMode is : %f", mode(test, length)); // mode fails to compile as integer is required, but double is provided
}