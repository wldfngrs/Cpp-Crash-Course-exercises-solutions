#define CATCH_CONFIG_MAIN
#include <stdexcept>
#include <optional>
#include "catch.hpp"

template <typename To, typename From>
std::optional<To> narrow_cast(From value) {
	const auto converted = static_cast<To>(value);
	const auto backwards = static_cast<From>(converted);
	if (value != backwards) return std::nullopt;
	return converted;
}

TEST_CASE("narrow cast reimplementation with std::optional") {
	// no narrowing - pass test
	int perfect{ 496 };
	const auto perfect_short = narrow_cast<short>(perfect);
	REQUIRE(perfect == perfect_short);
	
	// narrowing - fail test
	int cyclic{ 142857 };
	const auto cyclic_short = narrow_cast<short>(cyclic);
	REQUIRE_FALSE(cyclic == cyclic_short);
}