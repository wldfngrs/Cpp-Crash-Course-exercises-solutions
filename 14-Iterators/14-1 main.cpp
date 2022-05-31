#define CATCH_CONFIG_MAIN
#include <vector>
#include "catch.hpp"
#include <cstdio>

TEST_CASE("prev returns iterators at given offsets") {
	std::vector<unsigned char> mission{
		0x9e, 0xc4, 0xc1, 0x29,
		0x49, 0xa4, 0xf3, 0x14,
		0x74, 0xf2, 0x99, 0x05,
		0x8c, 0xe2, 0xb2, 0x2a
	};

	auto itr1 = mission.end();
	std::advance(itr1, -1);
	REQUIRE(*itr1 == 0x2a);

	auto itr2 = std::prev(itr1); // defaults to a distance of 1
	REQUIRE(*itr2 == 0xb2);

	auto itr3 = std::prev(itr1, 4);
	REQUIRE(*itr3 == 0x05);

	REQUIRE(*itr1 == 0x2a);
}

