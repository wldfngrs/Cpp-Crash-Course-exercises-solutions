#include <cstdio>
#include <cstdint>

template<typename Fn, typename In, typename Out>
constexpr Out fold(Fn function, In* input, size_t length, Out initial) {
	if (length == 0) {
		return initial;
	}

	else {
		for (size_t index = 0; index < length; index++) {
			initial = function(input[index], initial);
		}
		return initial;

	}
}


int main() {
	int data[]{ 100, 200, 300, 400, 500 };
	size_t data_len = 5;
	auto sum = fold([](auto x, auto y) {return x + y; }, data, data_len, 0);
	printf("Sum: %d\n", sum);
	auto maximum = fold([](auto x, auto y) { auto result = x >= y ? x : y; return result; }, data, data_len, data[1]);
	printf("Maximum: %d\n", maximum);
	auto minimum = fold([](auto x, auto y) { auto result = x <= y ? x : y; return result; }, data, data_len, data[1]);
	printf("Minimum: %d\n", minimum);
	int count{}, index{};
	auto over200 = fold([&](auto x, auto y) {if (x > 200) ++count; return data[index++]; }, data, data_len, 200);
	printf("Count over200: %d\n", count);
}
