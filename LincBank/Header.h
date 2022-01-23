/*
Header file holds all definitions of classes and interfaces.

*/
#include <iostream>
#include <vector>
using namespace std;

/*Below is the class definition for Transaction*/
class Transaction {
private:
	// These are Transaction's member variables:
	string desc;		// Stores a description of the transaction type. (Deposit, Withdrawal)
	time_t time_Stamp;	// Stores when the transaction was made. 
	double value;		// Stores the value of money that has been transacted. 
public:
	// Accessor methods.
	void set_Desc(string d);
	void set_Time_Stamp();
	void set_Value(double v);
	string get_Desc();
	char* get_Time_Stamp();
	double get_Value();
	// Member methods
	void to_String();	// Forms the data into a string which is printed to the screen.
	// Constructor method.
	Transaction(string d, double v);
};

/*Below is the abstract class definition for Account*/
class Account {
private:
	// Account's member variables:
	vector<Transaction> history;	// A vector to be filled with Transaction objects. 	
	double balance;					// Stores the balance for the account. 
public:
	// Accessors for dervived class functions.
	virtual double get_Overdraft() { return 0; }		// Gives access to overdraft in Current class from base class.
	virtual double compute_Intrest(int t) { return 0; } // Gives access to compute_intrest method in Saving class from base class. 
	// Pure virtual functions. 
	// Any class that inherates the Account clas needs these functions 
	virtual void deposit(double v) = 0;		
	virtual void withdraw(double v) = 0;	
	virtual void to_String() = 0;			
	// Accessor methods.
	void set_Balance(double b);
	double get_Balance();
	void set_History(Transaction t);
	vector<Transaction> get_History();
	// Public member varbiable.
	int account_Type = 0;			// Stores what type the account is in the form of an int. 1 current, 2 savings. 
};

/*Below is the interface Intrest_Earning*/
class Intrest_Earning {
public:
	// Public pure virtual method.
	// Any method that uses this interface needs this method in it.
	virtual double compute_Intrest(int t) = 0;
};

/*Below is the definition for the Current class, it inherates from Account*/
class Current : public Account {
private:
	// Member variables 
	double overdraft;	// Stores the overdraft ammount. max is 500 GBP.
public:
	// Current class constructor
	Current(double v);
	// Accessor methods 
	void set_Overdraft(double o);
	double get_Overdraft();
	// Virtual function overriders. 
	void to_String() override;			// Converts all the data into a nice format to be displayed to the user. 
	void deposit(double v) override;	// Increases the Balance and takes the overdraft into account.
	void withdraw(double v) override;	// Decreases the Balance and takes the overdraft into account.
};

/*Below is the definition for the Current class, it inherates from Account and uses interface Intrest_Earning.*/
class Savings : public Account, public Intrest_Earning {
private:
	// Savings's member variables. 
	double intrest_Rate;	// Stores the intrest rate. 0.85% for regular and 1.15% for ISA.
	bool isa;				//
public:
	// Constructor for Savings
	Savings(double v, bool b);
	// Virtual function overriding.
	void to_String() override;				// Converts data into a nice format then displays it to the user.
	double compute_Intrest(int t) override;	// Computes the intrest of the account after a designated amount of time. 
	void deposit(double v) override;		// Adds to the balance.
	void withdraw(double v) override;		// Removes from the balance.
};