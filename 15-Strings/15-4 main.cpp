#include <string>
#include <cstdio>
#include <iostream>
#include <vector>


int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Missing argument!\nUsage: hello.exe [argument]\n");
		return 0;
	}

	std::string argument;
	int index{ 1 };
	while (index < argc) {
		argument.append(argv[index]);
		index++;
	}

	std::string firstArg, secondArg;
	size_t indx;
	// addition
	indx = argument.find("+");
	if (indx != std::string::npos) {
		auto itr = argument.begin();
		auto signItr = itr + indx;
		firstArg.append(itr, signItr);
		secondArg.append(signItr + 1, argument.end());
		const auto firstArgLong = std::stoul(firstArg);
		const auto secondArgLong = std::stoul(secondArg);
		std::cout << firstArgLong + secondArgLong << std::endl;
	}

	indx = argument.find("*");
	if (indx != std::string::npos) {
		auto itr = argument.begin();
		auto signItr = itr + indx;
		firstArg.append(itr, signItr);
		secondArg.append(signItr + 1, argument.end());
		const auto firstArgLong = std::stoul(firstArg);
		const auto secondArgLong = std::stoul(secondArg);
		std::cout << firstArgLong * secondArgLong << std::endl;
	}

	indx = argument.find("-");
	if (indx != std::string::npos) {
		auto itr = argument.begin();
		auto signItr = itr + indx;
		firstArg.append(itr, signItr);
		secondArg.append(signItr + 1, argument.end());
		const auto firstArgLong = std::stoul(firstArg);
		const auto secondArgLong = std::stoul(secondArg);
		std::cout << firstArgLong - secondArgLong << std::endl;
	}

	indx = argument.find("/");
	if (indx != std::string::npos) {
		auto itr = argument.begin();
		auto signItr = itr + indx;
		firstArg.append(itr, signItr);
		secondArg.append(signItr + 1, argument.end());
		const auto firstArgLong = std::stoul(firstArg);
		const auto secondArgLong = std::stoul(secondArg);
		double long result = firstArgLong / secondArgLong;
		std::cout << result << std::endl;
	}
}