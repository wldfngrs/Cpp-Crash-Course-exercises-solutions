#include <iostream>
#include <chrono>
#include <utility>

struct TimerClass {
	// Basic constructor
	TimerClass(const char *name)
		: timestamp{ std::chrono::system_clock::now() },
		  name{name}
	{
	}
	
	// Destructor
	~TimerClass() {
		auto currentTime = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_time = currentTime - timestamp;
		if (moved_from == false) {
			printf("Lifetime of timer '%s': %f\n", name, elapsed_time.count());
		}
	}

	// Copy constructor
	TimerClass(const TimerClass& copy)
		: timestamp{ copy.timestamp },
		  name{copy.name}
	{
	}

	// Copy assignment
	TimerClass& operator=(const TimerClass& copy) {
		if (this == &copy) return *this;
		timestamp = copy.timestamp;
		name = copy.name;
		return *this;
	}

	// Move constructor
	TimerClass(TimerClass&& move) noexcept
		: timestamp{ move.timestamp },
		  name{move.name}
	{
		move.name = nullptr;
		move.moved_from = true;
	}

	// Move assignment
	TimerClass& operator=(TimerClass&& move) noexcept {
		if (this == &move) return *this;
		timestamp = move.timestamp;
		name = move.name;
		move.name = nullptr;
		move.moved_from = true;
		return *this;
	}

private:
	std::chrono::time_point<std::chrono::system_clock> timestamp;
	bool moved_from = false;
	const char* name;
};

void expensive_computation(TimerClass&& timer) {
	int n = 1;
	for (int i = 0; i < 10000000; i++)
	{
		n = (n * i * i) % 2021;
	}
}

int main() {
	TimerClass timer1{ "Timer 1" };
	TimerClass timer2{ "Timer2" };
	timer2 = timer1;
	TimerClass timer3{ "Timer 3" };
	expensive_computation(std::move(timer3));
}