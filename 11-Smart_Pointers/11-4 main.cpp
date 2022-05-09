#include <cstdio>
#include <memory>

struct Hal {
	Hal(std::shared_ptr<FILE> file, const char* name)
		: file{ file }, name{ name }
	{
		fprintf(file.get(), "Hello, %s\n", name);
	}
	~Hal() {
		fprintf(file.get(), "Stop, %s\n", name);
	}
	void write_status() {
		fprintf(file.get(), "%s is completely operational\n", name);
	}
	std::shared_ptr<FILE> file;
	const char* name;
};

int main() {
	auto file = fopen("HAL9000", "w");
	if (!file) return errno;
	std::shared_ptr<FILE> file_ptr{ file, fclose };
	Hal halter{ file_ptr, "halter"};
	Hal halter2{ file_ptr, "halter2"};
	halter2.write_status();
	halter.write_status();
	return 0;
}