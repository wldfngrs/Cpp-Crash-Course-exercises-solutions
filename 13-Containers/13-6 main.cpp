#include <chrono>
#include <cstdio>
#include <random>
#include <vector>
#include <map>

std::vector<int> FibonacciGenerator(const size_t elementNumber) {
	std::vector<int> resultVector;
	size_t result{};
	size_t previous{};
	size_t current{ 1 };
	for (size_t i = 0; i < elementNumber; i++) {
		result = previous + current;
		resultVector.emplace_back(result);
		previous = current;
		current = result;
	}
	return resultVector;
}

long fib_sum(size_t n) {
	auto FibonacciVector = FibonacciGenerator(n);
	size_t sum{};
	for (auto element : FibonacciVector) {
		sum += element;
	}
	return 0;
}

long random() {
	static std::mt19937_64 mt_engine{ 102787 };
	static std::uniform_int_distribution<long> int_d{ 1000, 2000 };
	return int_d(mt_engine);
}

struct StopWatch {
	StopWatch(std::chrono::nanoseconds& result)
		: result{result},
		start{ std::chrono::system_clock::now() } {}
	~StopWatch() {
		result = std::chrono::system_clock::now() - start;
	}
private:
	std::chrono::nanoseconds& result;
	const std::chrono::time_point<std::chrono::system_clock> start;
};

long cached_fib_sum(const size_t& n) {
	static std::map<long, long> cache;
	if (cache.find(n) == cache.end()) { // key does not exist
		auto sum = fib_sum(n);
		cache.insert({ n, sum });
		return sum;
	}
	else { // key exists
		return cache[n];
	}
	return 0;
}

int main() {
	size_t samples{ 1'000'000 };
	std::chrono::nanoseconds elapsed;
	{
		StopWatch stopwatch{ elapsed };
		volatile double answer;
		while (samples--) {
			answer = fib_sum(random());
			//answer = cached_fib_sum(random());
		}
	}
	printf("Elapsed: %g s.\n", elapsed.count() / 1'000'000.);
}

// computing the sum with the map container resulted in much much faster computation than
// plainly using the 'fib_sum' function.