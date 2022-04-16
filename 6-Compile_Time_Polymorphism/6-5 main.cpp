#include <cstdio>
#include <stdexcept>

struct ConsoleLogger {
	void log_transfer(long from, long to, double amount) {
		printf("%ld -> %ld: %f\n", from, to, amount);
	}
};

template <typename T>
struct Bank {
	void make_transfer(T from, T to, double amount) {
		logger.log_transfer(from, to, amount);
	}
	ConsoleLogger logger;
};

int main() {
	Bank<long>bank;
	bank.make_transfer(1000, 2000, 49.95);
	bank.make_transfer(2000, 4000, 20.00);
}