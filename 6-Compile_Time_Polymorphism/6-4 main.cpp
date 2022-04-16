#include <cstdio>
#include <stdexcept>

template <typename T, size_t Length>
T mean(T(&arr)[Length]) {
	T result{};
	for (size_t i{}; i < Length; i++) {
		result += arr[i];
	}
	return result / Length;
}

int main() {
	double nums_d[]{ 1.0,2.0,3.0,4.0 };
	auto result1 = mean(nums_d);
	printf("double array mean: %f\n", result1);

	float nums_f[]{ 1.0f, 2.0f, 3.0f, 4.0f };
	auto result2 = mean(nums_f);
	printf("float array mean: %f\n", result2);

	size_t nums_c[]{ 1,2,3,4 };
	auto result3 = mean(nums_c);
	printf("size_t array mean: %zd\n", result3);
}