#include <vector>
#include <cstdio>

template <typename T>
int sum(T objs) {
	int result{};
	for (auto obj : objs) {
		result += obj;
	}
	return result;
}

int main() {
	std::vector<int> objects{ 1,2,3,4,5 };
	printf("Sum of int objects: %d", sum(objects));
}