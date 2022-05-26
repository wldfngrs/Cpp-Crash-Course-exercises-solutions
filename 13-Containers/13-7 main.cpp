#define CATCH_CONFIG_MAIN
#include <stdexcept>
#include <vector>
#include <initializer_list>
#include "catch.hpp"
#include <iostream>
#include <cmath>

// still working on this, problem a little tougher than I initially deduced

template <typename T>
struct UnevenMatrix {
	UnevenMatrix(int numberOfRows, std::initializer_list<T> values)
		: rows{ numberOfRows },
		  data(numberOfRows, std::vector<T>{}) 
	{
		auto itr = values.begin();
		size = values.size();
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

	void print() {
		for (size_t i{}; i < rows; i++) {
			for (size_t j{}; j < columns; j++) {
				std::cout << data[i][j];
			}
			std::cout << std::endl;
		}
	}

	int rows;
	int columns;
	size_t size;
private:
	std::vector<std::vector<T>> data;
};

TEST_CASE("Uneven Matrix and std::initializer list") {
	UnevenMatrix<int> mat {
		5,
		{3,1,2,3,4,5,6,7,8}
	};

	mat.print();

	REQUIRE(mat.rows == 5);
}