#include <iostream>
#include <vector>
using namespace std;

class Transaction {
private:
	string desc;
	time_t time_Stamp;
	double value;
public:
	void set_Desc(string d);
	void set_Time_Stamp();
	void set_Value(double v);
	string get_Desc();
	char* get_Time_Stamp();
	double get_Value();
	void to_String();
	Transaction(string d, double v);
};

class Account {
private:
	vector<Transaction> history;
	double balance;
public:
	virtual void deposit(double v) = 0;
	virtual void withdraw(double v) = 0;
	virtual void to_String() = 0;
	void set_Balance(double b);
	double get_Balance();
	void set_History(Transaction t);
	vector<Transaction> get_History();
};

class Intrest_Earning {
public:
	virtual double compute_Intrest(int t) = 0;
};

class Current : public Account {
private:
	double overdraft;
public:
	void to_String() override;
	void set_Overdraft(double o);
	double get_Overdraft();
	Current(double v);
	void deposit(double v) override;
	void withdraw(double v) override;
};

class Savings : public Account, public Intrest_Earning {
private:
	double intrest_Rate;
	bool isa;
public:
	Savings(double v, bool b);
	void to_String() override;
	double compute_Intrest(int t) override;
	void deposit(double v) override;
	void withdraw(double v) override;
};