#include <cstdio>
#include <stdexcept>

// Account class with functions to set and get balance in specified account
struct Account {
	virtual void setBalance(double amount) = 0;
	virtual void getBalance() const = 0;

public:
	const char* accountName;
	double accountBalance;
};

struct CheckingAccount : Account {
	CheckingAccount(const char* name)
	{
		accountName = name;
		accountBalance = 10000;
	}
	void setBalance(double amount) override {
		accountBalance = accountBalance + amount;
	}

	void getBalance() const override {
		printf("\nBalance in %s : %f", accountName, accountBalance);
	}
};

struct SavingsAccount : Account {
	SavingsAccount(const char * name)
	{
		accountName = name;
		accountBalance = 10000;
	}
	void setBalance(double amount) override {
		accountBalance = accountBalance + amount;
	}

	void getBalance() const override {
		printf("\nBalance in %s  : %f", accountName, accountBalance);
	}
};

template <typename T>
struct Bank {
	void make_transfer(T& from, T& to, double amount) {
		to.setBalance(amount);
		from.accountBalance = from.accountBalance - amount;
		printf("\n%s -> %s :: %f", from.accountName, to.accountName, amount);
	}
};

int main() {
	CheckingAccount checkA{"checkA"};
	CheckingAccount checkB{"checkB"};
	CheckingAccount checkC{"checkC"};
	SavingsAccount saveA{ "saveA" };
	SavingsAccount saveB{ "saveB" };
	SavingsAccount saveC{ "saveC" };

	Bank<Account> bank;
	printf("---TRANSFERS---");
	bank.make_transfer(checkA, checkB, 10000);
	bank.make_transfer(checkC, checkA, 500);
	bank.make_transfer(saveA, saveB, 5000);
	bank.make_transfer(saveC, saveA, 200);
	printf("\n\n---BALANCE---");
	checkA.getBalance();
	checkB.getBalance();
	checkC.getBalance();
	saveA.getBalance();
	saveB.getBalance();
	saveC.getBalance();
	printf("\n");
}