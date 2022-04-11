#include <cstdio>

void read_from(char* array, int index) {
	int size = sizeof(array) / sizeof(char);
	if (index <= size && index >= 0) {
		printf("\nIndex %d of array, holds '%c'", index, array[index]);
	}
	else printf("\nOut of bounds!");
}

void write_to(char* array, int index, char character) {
	int size = sizeof(array) / sizeof(char);
	if (index <= size && index >= 0) {
		array[index] = character;
		printf("\nArray: %s", array);
	}
	else printf("\nOut of bounds");
}


int main() {
	char lower[] = "abc?e";
	char upper[] = "ABC?E";
	char* upper_ptr = upper;		// Equivalent: &upper[0]

	lower[3] = 'd';					// lower now contains a b c d e \0
	upper_ptr[3] = 'D';				// upper now contains A B C D E \0

	char letter_d = lower[3];		// letter_d equals 'd'
	char letter_D = upper_ptr[3];	// letter_D equals 'D'

	// Have fun with the functions as you please!
	read_from(lower, -10);
	write_to(upper, 2, 'F');
}