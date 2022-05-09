#include <cstdio>
#include <memory>

struct Hal {
	Hal(std::shared_ptr<FILE> file)
		: file{ file } {
		fprintf(file.get(), "Hello, Dave\n");
	}
	~Hal() {
		fprintf(file.get(), "Stop, Dave\n");
	}
	void write_status() {
		fprintf(file.get(), "I'm completely operational\n");
	}
	std::shared_ptr<FILE> file;
};

int main() {
	auto file = fopen("HAL9000", "w");
	if (!file) return errno;
	std::shared_ptr<FILE> file_ptr{ file, fclose };
	Hal halter{ file_ptr };
	halter.write_status();
	return 0;
}