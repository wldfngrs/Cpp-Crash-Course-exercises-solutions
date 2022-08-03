#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

void fileInfo(std::ifstream&);

int main() {
	std::cout << "Usage: info [file path]" << std::endl;
	std::string commandPath;
	std::getline(std::cin, commandPath);
	std::string command(commandPath.begin(), commandPath.begin()+4);
	std::string path(commandPath.begin()+5, commandPath.end());
	
	if (command != "info" ) {
		std::cout << "command '" << command << "' not found!\n \treturning 0..." << std::endl;
		return 0;
	}
	else {
		try {
			std::ifstream file(path.c_str(), std::ios_base::in);
			if (!file.is_open()) {
				std::string err{ "Unable to open file " };
				err.append("'");
				err.append(path);
				err.append("'");
				throw std::runtime_error{ err };
			}
			fileInfo(file);
		}
		catch (const std::exception& e) {
			std::cerr << "\tError occured: " << e.what() << std::endl;
		}
	}
}

void fileInfo(std::ifstream& f) {
	std::string word;
	size_t count{};
	size_t wordLength{};
	double averageWordLength{};
	std::unordered_map<char, int> counts;

	while (f >> word) {
		count++;
		
		for (int i = 0; i < word.length(); i++) {
			if ((word[i] == ',') || (word[i] == '.') || (word[i] == '?') || (word[i] == '!')) { continue; }
			++wordLength;
			word[i] = std::tolower(word[i]);
			counts[word[i]]++;
		}
	}

	std::cout << "Discovered " << count << " word(s)" << std::endl;
	averageWordLength = wordLength / count;
	std::cout << "Average word length: " << averageWordLength << std::endl;

	for (auto it = counts.cbegin(); it != counts.cend(); it++) {
		std::cout << it->first << ": ";
		auto elementCount = it->second;
		while (elementCount--) printf("*");
		printf("\n");
	}
}