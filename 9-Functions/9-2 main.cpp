#include <cstdint>
#include <cstdio>

int main(int argc, char** argv) {
	size_t index{};
	int count{};
	for (int i = 1; i <= argc; i++) {
		while(argv[i][index]){
			++count;
			++index;
		}

		printf("Argument #%d: ", i);
		for (int k = 0; k < count; k++) {
			printf("*");
		}
		printf("\n");
	}
}