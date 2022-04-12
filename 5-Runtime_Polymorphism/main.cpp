#include <cstdio>


// Note to self and other users of this code, you cant't instantiate a class containing pure virtual methods
// You can only declare a reference of the class type or pointer to the class type(the one containing pure virtual methods) and instantiate
// that with an instantiation of any of its derived classes.
// Eg: In this code solution, Logger is a class containing a pure virtual method, hence it cannot be instantiated.
//	   However, 'PurelyVirtualClass& pvc = DerivedClass dc' or ' PurelyVirtualClass* pvc = &DerivedClass dc' can utilize the member functions

struct Logger {
	virtual ~Logger() = default;
	virtual void log_transfer(long from, long to, double amount) = 0;
};

struct ConsoleLogger :Logger {
	ConsoleLogger(const char* logString)
		: logString{logString}
	{}
	void log_transfer(long from, long to, double amount) override {
		printf("[cons] %s's transaction :: %ld -> %ld: %f", logString, from, to, amount);
	}
private:
	const char* logString;
};

struct AccountDatabase {
	virtual void RetrieveAmount(long id) const = 0;

	virtual void SetAmount(long id, double amount) = 0;
};

struct InMemoryAccountDatabase :AccountDatabase {
	InMemoryAccountDatabase() : Balance{}{}
	void RetrieveAmount(long id) const override {
		printf("\nAmount at id[%ld] is %f", id, Balance[id]);
	}

	void SetAmount(long id, double amount) override {
		Balance[id] = amount ;
		printf("\n%f has been set in account id [%ld]", amount, id);
	}

private:
	double Balance[100]{};
};

struct Bank {
	Bank (Logger* logger, AccountDatabase& accountDatabase)
		: logger{logger},
		  accountDatabase{ accountDatabase } {}
	void set_logger(Logger* new_logger) {
		logger = new_logger;
	}

	void make_transfer(long from, long to, double amount) {
		if (logger) {
			logger->log_transfer(from, to, amount);
		}
	}

	void setBalance(long id, double amount){
		accountDatabase.SetAmount(id, amount);
	}

	void getBalance(long id) {
		accountDatabase.RetrieveAmount(id);
	}
private:
	Logger* logger;
	AccountDatabase& accountDatabase;
};

int main() {
	ConsoleLogger logger{ "Ben" };
	InMemoryAccountDatabase inMemory;
	Bank bank{ &logger, inMemory };
	bank.make_transfer(1800, 1801, 10000);
	bank.setBalance(5, 100);
	bank.getBalance(5);
	printf("\n");
}