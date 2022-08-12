#include <iostream>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

struct Attributes {
	Attributes& operator+=(const Attributes& other) {
		this->size_bytes += other.size_bytes;
		this->n_directories += other.n_directories;
		this->n_files += other.n_files;
		return *this;
	}

	size_t size_bytes;
	size_t n_directories;
	size_t n_files;
};

void print_line(const Attributes& attributes, string_view path) {
	cout << setw(14) << attributes.size_bytes
		<< setw(7) << attributes.n_files
		<< setw(7) << attributes.n_directories
		<< " " << path << "\n";
}

Attributes exploreRec(const directory_entry& directory) { // explore recursively
	Attributes attributes{};
	for (const auto& entry : recursive_directory_iterator{ directory.path() }) {
		if (entry.is_directory()) {
			attributes.n_directories++;
		}
		else {
			attributes.n_files++;
			attributes.size_bytes += entry.file_size();
		}
	}
	return attributes;
}

int main(int argc, const char** argv) {
	if (argc < 2) {
		cerr << "Usage: treedir [OPTIONS] [PATH]\n";
		return -1;
	}

	Attributes root_attributes{};
	if (argv[1][0] == '-') {
		string options{ argv[1] };
		const path sys_path{ argv[2] };
		for (int i = 1; i < options.length(); i++) {
			if (argv[1][i] == 'R') {
				cout << "-----Recursive Directory Iteration------\n";
				cout << "Size           Files  Dirs   Name\n";
				cout << "-------------- ------ ------ ------------\n";
				for (const auto& entry : directory_iterator{ sys_path }) {
					try {
						if (entry.is_directory()) {
							const auto attributes = exploreRec(entry);
							root_attributes += attributes;
							print_line(attributes, entry.path().string());
							root_attributes.n_directories++;
						}
						else {
							root_attributes.n_files++;
							error_code ec;
							root_attributes.size_bytes += entry.file_size(ec);
							if (ec) cerr << "Error reading file size: "
								<< entry.path().string() << endl;
						}
					}
					catch (const exception&) {
					}
				}
			}
		}
	}
	else {
		const path sys_path{ argv[1] };
		cout << "(*) => directory\n";
		cout << "------Directory Iteration------\n";
		cout << "Size          Name\n";
		cout << "------------- -----------------\n";
		for (const auto& entry : directory_iterator{ sys_path }) {
			if (entry.is_directory()) {
				cout << setw(14) << "* ";
			}
			else {
				root_attributes.size_bytes += entry.file_size();
				cout << setw(13) << entry.file_size() << " ";
				error_code ec;
				if (ec) cerr << "Error reading file size: "
					<< entry.path().string() << endl;
			}
			
			cout << entry.path().filename().string() << "\n";
		}
	}

	print_line(root_attributes, argv[2]);
}