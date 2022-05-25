#define CATCH_CONFIG_MAIN
#include <stdexcept>
#include <vector>
#include <initializer_list>
#include "catch.hpp"

template <typename T>
struct UnevenMatrix {
	UnevenMatrix(int numberOfRows, std::initializer_list<T> values)
		: rows{ numberOfRows },
		  data(numberOfRows, std::vector<T>{}) 
	{
		auto itr = values.begin();
		const size_t size = values.size();
		columns = size / rows;
		for (size_t column{}; column < columns; column++) {
			data[column].assign(itr, itr + columns);
			itr += columns;
		}
	}

	T& at(size_t row, size_t col) {
		if (row >= rows || col >= columns) {
			throw std::out_of_range{"Index is invalid"};
		}
		return data[row][col];
	}
	int rows;
	int columns;
private:
	std::vector<std::vector<T>> data;
};

TEST_CASE("Uneven Matrix and std::initializer list") {
	UnevenMatrix<int> mat {
		3,
		{3,1,2,
		3,4,5,
		6,7,8}
	};

	REQUIRE(mat.rows == 3);
	REQUIRE(mat.at(2, 2) == 8);
}