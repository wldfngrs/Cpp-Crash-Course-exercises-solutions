#include <future>
#include <iostream>
#include <atomic>

using namespace std;

struct SpinLock {
	SpinLock() {};
	SpinLock(const SpinLock&) = delete;
	SpinLock& operator=(SpinLock&) = delete;

	void lock() {
		while (toggle.test_and_set(std::memory_order_acquire)) {}
	}
	
	bool try_lock() {
		if (toggle.test_and_set(std::memory_order_acquire)) { return false; }
		return true;
	}
	
	void unlock() {
		toggle.clear(std::memory_order_release);
	}

private:
	std::atomic_flag toggle = ATOMIC_FLAG_INIT;
};

void goat_rodeo() {
	const size_t iterations{ 1'000'000 };
	int tin_cans_available{};
	SpinLock tin_can_mutex;

	auto eat_cans = std::async(std::launch::async, [&] {
		for (size_t i{}; i < iterations; i++) {
			std::lock_guard<SpinLock> guard{ tin_can_mutex };
			tin_cans_available--;
		}
	});

	auto deposit_cans = std::async(std::launch::async, [&] {
		for (size_t i{}; i < iterations; i++) {
			std::lock_guard<SpinLock> guard{ tin_can_mutex };
			tin_cans_available++;
		}
	});

	eat_cans.get();
	deposit_cans.get();
	std::cout << "Tin cans: " << tin_cans_available << "\n";
}

int main() {
	goat_rodeo();
	goat_rodeo();
	goat_rodeo();
}