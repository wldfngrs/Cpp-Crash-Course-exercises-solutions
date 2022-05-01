#include <cstdint>
#include <cstdio>

template <typename Fn, typename In>
constexpr bool all(Fn function, In* input, size_t length) {
	bool check = true;
	for (size_t index{}; index < length; index++) {
		check = function(input[index]);
		if (check == false) {
			break;
		}
	}
	return check;
}

int main() {
	int data[]{100, 200, 300, 400, 500};
	size_t data_len = 5;
	auto all_gt100 = all([](auto x) {return x > 100; }, data, data_len);
	if (all_gt100) printf("All elements greater than 100. :]\n");
	else printf("Check failed. :[");
}