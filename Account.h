#pragma once
#include <fstream>
#include <fstream>
class Account{
private:
	double balance;
public:
	Account();
	~Account();
	double getBalance();
	void setBalance(double bal);
	double disburstSalary(double sal);
	void readAccount();
	void writeAccount();
};

