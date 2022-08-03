#include <cstdint>
#include <cstdio>
#include <functional>
#include <stdexcept>
#include <exception>
#include <iostream>
using namespace std;

struct SpeedUpdate {
	double velocity_mps;
};

struct CarDetected {
	double distance_m;
	double velocity_mps;
};

struct BrakeCommand {
	double time_to_collision_s;
};

struct SpeedLimitDetected {
	unsigned short speed_mps;
};


using SpeedUpdateCallback = std::function<void(const SpeedUpdate&)>;
using CarDetectedCallback = std::function<void(const CarDetected&)>;
using SpeedLimitCallback = std::function<void(const SpeedLimitDetected&)>;

struct IServiceBus {
	virtual ~IServiceBus() = default;
	virtual void publish(const BrakeCommand&) = 0;
	virtual void subscribe(SpeedUpdateCallback) = 0;
	virtual void subscribe(CarDetectedCallback) = 0;
	virtual void subscribe(SpeedLimitCallback) = 0;
};

struct MockServiceBus : IServiceBus {
	void publish(const BrakeCommand& cmd) override {
		commands_published++;
		last_command = cmd;
	}
	void subscribe(SpeedUpdateCallback callback) override {
		speed_update_callback = callback;
	}
	void subscribe(CarDetectedCallback callback) override {
		car_detected_callback = callback;
	}

	void subscribe(SpeedLimitCallback callback) override {
		speed_limit_callback = callback;
	}

	BrakeCommand last_command{};
	int commands_published{};
	SpeedUpdateCallback speed_update_callback{};
	CarDetectedCallback car_detected_callback{};
	SpeedLimitCallback speed_limit_callback{};
};

struct AutoBrake {
	AutoBrake(IServiceBus& bus)
		: collision_threshold_s{ 5 },
		speed_mps{} {
		bus.subscribe([this](const SpeedUpdate& update) {
			speed_mps = update.velocity_mps;
			});
		bus.subscribe([this, &bus](const CarDetected& cd) {
			const auto relative_velocity_mps = speed_mps - cd.velocity_mps;
			const auto time_to_collision_s = cd.distance_m / relative_velocity_mps;
			if (time_to_collision_s > 0 &&
				time_to_collision_s <= collision_threshold_s) {
				bus.publish(BrakeCommand{ time_to_collision_s });
			}
			});
		bus.subscribe([this, &bus](const SpeedLimitDetected& sld) {
			last_known_speed_limit_ms = sld.speed_mps;
			if (last_known_speed_limit_ms < sld.speed_mps) {
				bus.publish(BrakeCommand{ 3 });
			}
			});
	}

	AutoBrake()
		: collision_threshold_s{ 5 },
		speed_mps{ 10 } {

	}

	void set_collision_threshold_s(double x) {
		if (x < 1) throw std::exception{ "Collision less than 1." };
		collision_threshold_s = x;
	}
	double get_collision_threshold_s() const {
		return collision_threshold_s;
	}
	double get_speed_mps() const {
		return speed_mps;
	}
	double get_last_known_speed_limit() const {
		return last_known_speed_limit_ms;
	}

	double collision_threshold_s;
	double speed_mps;
	double last_known_speed_limit_ms{ 35 };
};

ostream& operator<<(ostream& s, AutoBrake a) {
	s << "Current collision threshold: " << a.collision_threshold_s
		<< "\nSpeed: " << a.speed_mps
		<< "\nLast known speed limit: " << a.last_known_speed_limit_ms;
	return s;
}

void assert_that(bool statement, const char* message) {
	if (!statement) throw std::runtime_error{ message };
}

void run_test(void(*unit_test)(), const char* name) {
	try {
		unit_test();
		printf("[+] Test %s successful.\n", name);
	}
	catch (const std::exception& e) {
		printf("[-] Test falure in %s. %s.\n", name, e.what());
	}
}

void initial_speed_is_zero() {
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };
	assert_that(auto_brake.get_speed_mps() == 0L, "speed not equal 0");
}

void initial_sensitivity_is_five() {
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };
	assert_that(auto_brake.get_collision_threshold_s() == 5L,
		"sensitivity is not 5");
}

void sensitivity_greater_than_1() {
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };
	try {
		auto_brake.set_collision_threshold_s(0.5L);
	}
	catch (const std::exception&) {
		return;
	}
	assert_that(false, "no exception thrown");
}

void speed_is_saved() {
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };

	bus.speed_update_callback(SpeedUpdate{ 100L });
	assert_that(100L == auto_brake.get_speed_mps(), "speed not saved to 100");
	bus.speed_update_callback(SpeedUpdate{ 50L });
	assert_that(50L == auto_brake.get_speed_mps(), "speed not saved to 50");
	bus.speed_update_callback(SpeedUpdate{ 0L });
	assert_that(0L == auto_brake.get_speed_mps(), "speed not saved to 0");
}

void match_last_known_speed_limit() {
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };

	bus.speed_limit_callback(SpeedLimitDetected{ 100 });
	assert_that(100 == auto_brake.get_last_known_speed_limit(), "100 was not logged/checked");
	bus.speed_limit_callback(SpeedLimitDetected{ 150 });
	assert_that(150 == auto_brake.get_last_known_speed_limit(), "150 was not logged/checked");
	bus.speed_limit_callback(SpeedLimitDetected{ 200 });
	assert_that(200 == auto_brake.get_last_known_speed_limit(), "200 was not logged/checked");
}

void no_brake_when_less_than_speed_limit() { // current speed limit is 35
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };

	bus.speed_limit_callback(SpeedLimitDetected{ 34 });
	assert_that(bus.commands_published == 0, "brake command published for less than speed limit");
}

void no_brake_when_more_than_speed_limit() { // current speed limit is 35
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };

	bus.speed_limit_callback(SpeedLimitDetected{ 36 });
	assert_that(bus.commands_published == 0, "brake command published for more than speed limit");
}

void no_alert_when_not_iminent() {
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };
	auto_brake.set_collision_threshold_s(2L);
	bus.speed_update_callback(SpeedUpdate{ 100L });
	bus.car_detected_callback(CarDetected{ 1000L, 50L });
	assert_that(bus.commands_published == 0, "brake commands were published");
}

void alert_when_imminent() {
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };
	auto_brake.set_collision_threshold_s(10L);
	bus.speed_update_callback(SpeedUpdate{ 100L });
	bus.car_detected_callback(CarDetected{ 100L, 0L });
	assert_that(bus.commands_published == 1, "1 brake command was not published");
	assert_that(bus.last_command.time_to_collision_s == 1L, "time to collision not computed correctly.");
}

void detect_speed_limit() {
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };
	bus.speed_limit_callback(SpeedLimitDetected{ 10 });
	assert_that(auto_brake.get_last_known_speed_limit() == 10, "speed limit was not detected");
}

void check_last_known_speed_limit() {
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };
	assert_that(auto_brake.get_last_known_speed_limit() == 35, "last known speed limit is not 39");
}

int main() {
	run_test(initial_speed_is_zero, "initial speed is 0");
	run_test(initial_sensitivity_is_five, "initial sensitivity is 5");
	run_test(sensitivity_greater_than_1, "sensitivity greater than 1");
	run_test(speed_is_saved, "speed is saved");
	run_test(no_alert_when_not_iminent, "no alert when iminent");
	run_test(alert_when_imminent, "alert when iminent");
	run_test(detect_speed_limit, "detect speed limit");
	run_test(check_last_known_speed_limit, "last known speed limit is 39");
	run_test(match_last_known_speed_limit, "last known speed was matched");
	run_test(no_brake_when_less_than_speed_limit, "no brake when current speed less than stored speed limit");
	run_test(no_brake_when_more_than_speed_limit, "brake command when current speed is more than less stored speed limit");

	AutoBrake ab;
	cout << "\n" <<  ab << endl;
}