#include "Account.h"
#include <fstream>


Account::Account() {
	readAccount();
}

Account::~Account() {
	writeAccount();
}


void Account::readAccount() {
	std::ifstream readAccount;
	readAccount.open("Accounts.txt");
	if (!readAccount.fail()) {
		readAccount >> balance;
	}
	readAccount.close();
}

void Account:: writeAccount() {
	std::ofstream writeAccount;
	writeAccount.open("Accounts.txt");

	if (!writeAccount.fail()) {
		writeAccount << balance;
	}
	writeAccount.close();
}

double Account::getBalance() {
	return balance;
}

void Account::setBalance(double bal){
	balance += bal;
}

double Account::disburstSalary(double sal)
{
	if (balance >= sal) {
		balance -= sal;
	}
	else {
		return balance - sal;
	}
}
