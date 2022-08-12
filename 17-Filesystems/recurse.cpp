#include <iostream>
#include <filesystem>

void findExt(const std::filesystem::directory_entry& directory, std::string ext) {
	for (const auto& entry : std::filesystem::recursive_directory_iterator{ directory }) {
		try {
				if (entry.path().extension() == ext) {
					std::cout << 
						std::setw(43) << entry.path().filename().string() << " " << std::setw(4) << entry.path().extension().string() << "\n";
				}
		} catch(const exception&) {}
	}
}

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cerr << "Usage: recurse [PATH] [EXTENSION]";
		return -1;
	}

	const std::filesystem::directory_entry directory{ argv[1] };
	const auto extension = argv[2];

	std::cout << "Path                                        Extension\n";
	std::cout << "------------------------------------------- ---------\n";
	findExt(directory, extension);
}
