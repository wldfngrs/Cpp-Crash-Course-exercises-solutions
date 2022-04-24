#include <cstdio>
#include <cstdint>
#include <string>
#include <iostream>
#include <iterator>
#include <cstdlib>
#include <stdexcept>
using namespace std;

string s; // this feels extremely hacky and I will work on handling this better in time, for now...well, the exercise is solved! :)

struct UnsignedBigInteger {
	UnsignedBigInteger(const char* data_ptr) : data_ptr{ data_ptr } {
		size_t size = strlen(data_ptr);
		if (size > 10) throw std::runtime_error{ "Overflow" };
	}

	UnsignedBigInteger operator+(UnsignedBigInteger& other) {
		size_t first = atoi(data_ptr);
		size_t second = atoi(other.data_ptr);
		s = to_string(first + second);
		const char* result_array = s.c_str();
		UnsignedBigInteger result{ result_array };
		return result;
	}

	UnsignedBigInteger operator+(int other) {
		size_t first = atoi(data_ptr);
		s = to_string(other + first);
		const char* result_array = s.c_str();
		UnsignedBigInteger result{ result_array };
		return result;
	}

	UnsignedBigInteger operator-(UnsignedBigInteger& other) {
		size_t first = atoi(data_ptr);
		size_t second = atoi(other.data_ptr);
		if (first < second) { // had to, as size_t is unsigned and narrowing into an int is what will permit displaying as a signed negative value.
			int intResult = first - second;
			s = to_string(intResult);
			const char* result_array = s.c_str();
			UnsignedBigInteger result{ result_array };
			return result;
		}
		else {
			s = to_string(first - second);
			const char* result_array = s.c_str();
			UnsignedBigInteger result{ result_array };
			return result;
		}
	}

	UnsignedBigInteger operator-(int other) {
		size_t first = atoi(data_ptr);
		size_t second = other;
		if (first < other) { // had to, as size_t is unsigned and narrowing into an int is what will permit displaying as a signed negative value.
			int intResult = first - other;
			s = to_string(intResult);
			const char* result_array = s.c_str();
			UnsignedBigInteger result{ result_array };
			return result;
		}
		else {
			s = to_string(first - other);
			const char* result_array = s.c_str();
			UnsignedBigInteger result{ result_array };
			return result;
		}
	}

	UnsignedBigInteger operator*(UnsignedBigInteger& other) {
		size_t first = atoi(data_ptr);
		size_t second = atoi(other.data_ptr);
		s = to_string(first * second);
		const char* result_array = s.c_str();
		UnsignedBigInteger result{ result_array };
		return result;
	}

	UnsignedBigInteger operator*(int other) {
		size_t first = atoi(data_ptr);
		s = to_string(first * other);
		const char* result_array = s.c_str();
		UnsignedBigInteger result{ result_array };
		return result;
	}

	UnsignedBigInteger operator%(UnsignedBigInteger& other) {
		size_t first = atoi(data_ptr);
		size_t second = atoi(other.data_ptr);
		s = to_string(first % second);
		const char* result_array = s.c_str();
		UnsignedBigInteger result{ result_array };
		return result;
	}

	UnsignedBigInteger operator%(int other) {
		size_t first = atoi(data_ptr);
		s = to_string(first % other);
		const char* result_array = s.c_str();
		UnsignedBigInteger result{ result_array };
		return result;
	}

	UnsignedBigInteger operator/(UnsignedBigInteger& other) {
		double first = atoi(data_ptr);
		double second = atoi(other.data_ptr);
		double resultDouble = first / second;
		s = to_string(resultDouble);
		const char* result_array = s.c_str();
		UnsignedBigInteger result{ result_array };
		return result;
	}

	UnsignedBigInteger operator/(int other) {
		double first = atoi(data_ptr);
		double second = other;
		double resultDouble = first / second;
		s = to_string(resultDouble);
		const char* result_array = s.c_str();
		UnsignedBigInteger result{ result_array };
		return result;
	}

	UnsignedBigInteger& operator=(int convert) { // convert from user-defined type to an int
		s = to_string(convert);
		this->data_ptr = s.c_str();
		return *this;
	}

	explicit operator int() const {
		int val = atoi(this->data_ptr);
		return val;
	}


	const char *data_ptr; // 10-byte array for internal representation
};

UnsignedBigInteger operator+(int first, UnsignedBigInteger& other) {
	size_t second = atoi(other.data_ptr);
	s = to_string(second + first);
	const char* result_array = s.c_str();
	UnsignedBigInteger result{ result_array };
	return result;
}

UnsignedBigInteger operator-(int firstInt, UnsignedBigInteger& other) {
	size_t second = atoi(other.data_ptr);
	size_t first = firstInt;
	if (first < second) { // had to, as size_t is unsigned and narrowing into an int is what will permit displaying as a signed negative value.
		int intResult = second - first;
		s = to_string(intResult);
		const char* result_array = s.c_str();
		UnsignedBigInteger result{ result_array };
		return result;
	}
	else {
		s = to_string(first - second);
		const char* result_array = s.c_str();
		UnsignedBigInteger result{ result_array };
		return result;
	}
}

UnsignedBigInteger operator*(int first, UnsignedBigInteger& other) {
	size_t second = atoi(other.data_ptr);
	s = to_string(first * second);
	const char* result_array = s.c_str();
	UnsignedBigInteger result{ result_array };
	return result;
}

UnsignedBigInteger operator%(int first, UnsignedBigInteger& other) {
	size_t second = atoi(other.data_ptr);
	s = to_string(first % second);
	const char* result_array = s.c_str();
	UnsignedBigInteger result{ result_array };
	return result;
}

UnsignedBigInteger operator/(int firstInt, UnsignedBigInteger& other) {
	double second = atoi(other.data_ptr);
	double first = firstInt;
	double resultDouble = first / second;
	s = to_string(resultDouble);
	const char* result_array = s.c_str();
	UnsignedBigInteger result{ result_array };
	return result;
}


int main() {
	try {
		UnsignedBigInteger test3{ "3" };
		UnsignedBigInteger test4{ "4" };
		auto a = test3 + test4;
		printf("[+]  3 + 4  = %s\n", a.data_ptr);

		UnsignedBigInteger test5{ "5" };
		UnsignedBigInteger test6{ "6" };
		auto b = test5 - test6;
		printf("[-]  5 - 6  = %s\n", b.data_ptr);

		auto c = test3 * test4;
		printf("[*]  3 x 4 = %s\n", c.data_ptr);

		auto d = test6 % test4;
		printf("[mod]  6 mod 4 = %s\n", d.data_ptr);

		auto e = test6 / test3;
		printf("[/]  6 / 3 = %s\n", e.data_ptr);

		UnsignedBigInteger testIntAdd1{ "3" };
		auto f = testIntAdd1 + 4;
		printf("[int+] 3 + 4 = %s\n", f.data_ptr);

		UnsignedBigInteger testIntAdd2{ "5" };
		auto g = 5 + testIntAdd2;
		printf("[int+] 5 + 5 = %s\n", g.data_ptr);

		test3 = test4;
		printf("[=] test3 = %s\n", test3.data_ptr);

		UnsignedBigInteger testCast{ "1333333333333333333" };
		int test = 1;
		test = static_cast<int>(testCast);
		if (test == atoi(testCast.data_ptr))
		{
			printf("[conversion] test = %d\n", test);
		}
		else {
			throw std::overflow_error{ "Overflow!" };
		}
	}
	catch (const std::exception& e) {
		printf("%s: Not enough memory for object initialization!\n", e.what());
	}
	catch (const std::runtime_error& e) {
		printf("%s: Narrowing occured!\n", e.what());
	}
}