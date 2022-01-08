#include <iostream>
#include <vector>
using namespace std;

class Transaction {
private:
	string desc;
	time_t time_Stamp;
	float value;
public:
	void set_Desc(string d);
	void set_Time_Stamp();
	void set_Value(float v);
	string get_Desc();
	char* get_Time_Stamp();
	float get_Value();
	void to_String();
	Transaction(string d, float v);
};

class Account {
private:
	vector<Transaction> history;
	float balance;
public:
	virtual void deposit(float v) = 0;
	virtual void withdraw(float v) = 0;
	virtual void to_String() = 0;
	void set_Balance(float b);
	float get_Balance();
	void set_History(Transaction t);
};

class Intrest_Earning {
public:
	void compute_Intrest();
};

class Current : public Account {
private:
	float overdraft;
public:
	void to_String() override;
	void set_Overdraft(float o);
	float get_Overdraft();
	Current(float v);
	void deposit(float v);
	void withdraw(float v);
};

class Savings : public Account , public Intrest_Earning {
private:
	float intrest_Rate;
	bool isa;
public:
	void to_String() override;
};
