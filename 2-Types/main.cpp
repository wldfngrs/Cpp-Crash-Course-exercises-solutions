#include <cstdio>

enum class Operation {
	Add,
	Subtract,
	Multiply,
	Divide
};

struct Calculator {
	Calculator(Operation operation) {
		// Used the this member-of operator (will be introduced in a chapter or two)
		this->operation = operation; 
	}

	int calculate(int a, int b) {
		switch (operation) {
		case Operation::Add: {
			return a + b;
		}
		case Operation::Subtract: {
			return a - b;
		}
		case Operation::Multiply: {
			return a * b;
		}
		case Operation::Divide: {
			return a / b;
		}
		default:
			printf("Invalid Operation!");
		}
	}

private:
	Operation operation;
};

int main() {
	Calculator calculatorAdd(Operation::Add);
	Calculator calculatorSubtract(Operation::Subtract);
	Calculator calculatorMultiply(Operation::Multiply);
	Calculator calculatorDivide(Operation::Divide);

	// Experiment as required or you wish!
	printf("The sum of 7 and 4 is %d", calculatorAdd.calculate(7, 4));
}