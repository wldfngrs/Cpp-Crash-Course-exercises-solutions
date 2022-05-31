#include <chrono>
#include <random>

struct Stopwatch {
	Stopwatch(std::chrono::nanoseconds& result)
		: result{ result },
		start{std::chrono::high_resolution_clock::now()} {}
	~Stopwatch() {
		result = std::chrono::high_resolution_clock::now() - start;
	}
private:
	std::chrono::nanoseconds& result;
	const std::chrono::time_point<std::chrono::high_resolution_clock> start;
};

long random() {
	static std::mt19937_64 mt_engine{ 1027 };
	static std::uniform_int_distribution<long> int_d{ 0, 1000 };
	return int_d(mt_engine);
}

int main() {
	std::chrono::nanoseconds elapsed;
	std::chrono::nanoseconds elapsed2;
	size_t size{1'000'000};
	std::vector<long> vec(size);
	std::forward_list<long> list(size);
	std::generate(vec.begin(), vec.end(), random);
	std::generate(list.begin(), list.end(), random);
	{
		Stopwatch duration{ elapsed };
		auto itr = vec.begin();
		while (itr != vec.end()) {
			std::advance(itr, 1);
		}
	}
	printf("Duration for traversing large vector: %lldms\n", elapsed.count() / 1'000'000);

	{
		Stopwatch duration{ elapsed2 };
		auto itr = list.begin();
		while (itr != list.end()) {
			std::advance(itr, 1);
		}
	}
	printf("Duration for traversing large forward list: %lldms\n", elapsed2.count() / 1'000'000);
}

// regardless of the number of elements in either container, traversing
// a vector is faster than traversing a forward list.