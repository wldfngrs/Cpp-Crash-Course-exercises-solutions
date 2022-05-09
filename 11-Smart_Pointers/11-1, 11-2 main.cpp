#include <cstdio>
#include <memory>

using FileGuard = std::shared_ptr<FILE>;

void say_hello(FileGuard file) {
	fprintf(file.get(), "HELLO DAVE");
}

int main() {
	auto file = fopen("HAL9000", "w");
	if(!file) return errno;
	FileGuard file_guard{ file, fclose };
	say_hello(file_guard);
	say_hello(file_guard); //additional call to say_hello
	return 0;
}
