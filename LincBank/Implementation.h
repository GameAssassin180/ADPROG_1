/*
Implementation file holds all impelemented methods for classes in Header file. 
*/
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <cmath>
#include <iomanip>
#include "Header.h";
using namespace std;

//Transaction class methods.
//Accessors Methods.
//Setting.
void Transaction::set_Desc(string d){desc = d;}
void Transaction::set_Time_Stamp(){time_Stamp = time(0);} // Sets variable to current time.
void Transaction::set_Value(double v){value = v;}
//Getting.
string Transaction::get_Desc(){return desc;}
char* Transaction::get_Time_Stamp(){char* time = ctime(&time_Stamp);return time;} // Returms the time in the following format Jan 15 11:41:16 2022
double Transaction::get_Value(){return value;}
//Constructor for transactions class.
Transaction::Transaction(string d, double v)
{
	set_Desc(d);
	set_Time_Stamp();
	set_Value(v);
}
//Code for to_String method.
void Transaction::to_String()
{
	/*
		Prints to the screen the infromation stored when a new transaction is created.
		Example: >>> Deposit: £500.00 At Jan 15 11:41:16 2022
	*/
	cout << ">>> " << get_Desc() << ": " << char(156) << fixed << setprecision(2) << get_Value() << " at " << get_Time_Stamp();
}


//Account class methods.
//Accessor methods.
//Setting.
void Account::set_Balance(double b){balance = b;}
void Account::set_History(Transaction t){history.push_back(t);}	// Pushes a transaction object back to the history vector.
//Getting.
double Account::get_Balance(){return balance;}
vector<Transaction> Account::get_History(){return history;}		// Returns the transaction vector.


//Current class methods.
//Accessor methods.
//Setting.
void Current::set_Overdraft(double o){overdraft = o;}
//Getting.
double Current::get_Overdraft(){return overdraft;}
//Code for to_String method.
void Current::to_String()
{
	cout << ">>> Current Account" << endl;
	cout << ">>> Current balance is: " << char(156) << get_Balance() << endl;
	cout << ">>> Current overdraft is: " << char(156) << overdraft << "\n" << endl;
	// Loops through the history vector and prints the most recent transaction to the screen. 
	for (int i = get_History().size(); i > 0; i--)
	{			
		get_History()[i - 1].to_String();
	}
	/*
		Example:
		>>> Current Account
		>>> Current balance is: £54.71
		>>> Current overdraft is: £500

		>>> Withdrawal: £0.89 at Sat Jan 16 12:25:28 2022
		>>> Deposit: £5.60 at Sat Jan 16 12:25:18 2022
		>>> Initial Deposit: £50.00 at Sat Jan 16 12:25:12 2022
	*/
}
//Constructor for Current class.
Current::Current(double v)
{
	if (v == 0)		// If the user doesnt want to make an opening deposit.
	{
		overdraft = 500;
		account_Type = 1;
	}
	else			// If the user does want to make an opening deposit.
	{
		Transaction t("Initial Deposit", v);	// Creates a new transaction object.
		overdraft = 500;						
		set_History(t);							// Pushes the new transaction back to the history vector.
		set_Balance(v);							// Sets the balance to the value of the initial deposit.
		account_Type = 1;						// Sets the account type to one so that a current account can be identified. 
	}
}
//Deposit functon.
void Current::deposit(double v)
{
	if (get_Overdraft() == 500)		// If the overdraft is full.
	{
		Transaction t("Deposit", v);		// Creates a new trasnaction object.
		set_History(t);						// Pushes the transaction back to the history vector.
		set_Balance(get_Balance() + v);		// Adds the deposited value to the balance.
		cout << ">>> Success!!!" << endl;	// Informs the user that its been done.
	}
	else if (overdraft == 0 and v <= 500 or overdraft < 500 and v < 500 - overdraft)	// If the overdraft isnt full and the value deposited wont fill the overdraft.
	{
		Transaction ot("Overdraft Deposit", v);
		overdraft = (overdraft + v);		// Adds the value to the overdraft.
		set_History(ot);
		cout << ">>> Success!!!" << endl;
	}
	else if (overdraft == 0 and v > 500)	// If the overdraft is empty and the value deposited is over then 500.
	{
		double temp = v - 500;	// Takes away the max overdraft from value entered. 
		Transaction ot("Overdraft Deposit", 500);
		Transaction t("Deposit", temp);
		overdraft = 500;	// Sets the overdraft to 500.
		set_Balance(temp);	// Sets the balnce to whats left over.
		set_History(ot);
		set_History(t);
		cout << ">>> Success!!!" << endl;
	}
	else if (overdraft < 500 and v > 500 - overdraft)	//If the overdraft is less then 500 and the deposit is more then is needed to fill it. 
	{
		double temp = v - (500 - overdraft); // Find whats left after the overdraft is filled.
		Transaction ot("Overdraft Deposit", 500 - overdraft);
		Transaction t("Desposit", temp);
		overdraft = 500;
		set_Balance(temp);
		set_History(t);
		set_History(ot);
		cout << ">>> Success!!!" << endl;
	}
}
//Withdrawal function.
void Current::withdraw(double v)
{
	if (overdraft == 0 and get_Balance() == 0)		// If both the balance and the overdraft are empty.
	{
		cout << ">>> Overdraft empty cannot withdraw." << endl;
	}
	else if (get_Balance() == 0 and overdraft < v)	// If the balance is empty and the value is greater then the overdraft.
	{
		// Tells the users they cant withdraw and how much they have.
		cout << ">>> Withdrawal too big not enough in overdraft" << endl;
		cout << ">>> Current overdraft is: " << char(156) << overdraft << endl;
	}
	else if (get_Balance() == 0 and overdraft >= v)	// If balance is empty and the overdraft has sufficient funds.
	{
		Transaction t("Overdraft Withdrawal", v);	// Create new transaction object.
		set_History(t);								// Pushes the transaction to the history vector.
		overdraft = (overdraft - v);				// Removes from the overdraft.
		cout << ">>> Success!!!" << endl;			// Tells the users that it has happened.
	}
	else if (get_Balance() <= v and overdraft <= (v - get_Balance()))	// If the balance is less then the value and the overdraft is less then whats left.
	{
		// Informs the user that they cant withdraw. 
		cout << ">>> Withdrawal too big not enough in overdraft" << endl;
		cout << ">>> Current balance is: " << char(156) << get_Balance() << endl;
		cout << ">>> Current overdraft is: " << char(156) << overdraft << endl;
	}
	else if (get_Balance() <= v and overdraft >= (v - get_Balance()))	// If the balance is less then the value and the overdraft is more then whats left.
	{
		double temp = (v - get_Balance());				// Takes the balance away from the value.
		Transaction t("Withdrawal", get_Balance());		// Makes a new transaction.
		set_Balance(0);									// Sets the balance to 0.
		Transaction ot("Overdraft Withdrawal", temp);	// Makes a new transaction with whats left after the balance is removed.
		overdraft = (overdraft - temp);					// Removes the remainder from the overdraft.
		set_History(t);									// Pushes back the first transaction.
		set_History(ot);								// Pushes back the second transaction.
		cout << ">>> Success!!!" << endl;				// Tells the user that its worked.
	}
	else if (get_Balance() >= v)	// If the balance is greater then the value. 
	{
		Transaction t("Withdrawal", v);
		set_Balance(get_Balance() - v);
		set_History(t);
		cout << ">>> Success!!!" << endl;
	}
}

//Savings account methods.
//Constructor.
Savings::Savings(double v, bool b)
{
	if (b == true and v >= 1000)	// Creates an ISA account.
	{
		isa = true;
		intrest_Rate = 0.0115;
		Transaction t("Initial Deposit", v);
		set_History(t);
		set_Balance(v);
		account_Type = 2;
	}
	else if (b == true and v < 1000)	// Informs the user why they cant open an ISA.
	{
		cout << ">>> Account cannot be opened unless 1000 GBP is deposited" << endl;
	}
	else if (b == false) // Creates a regular savings account.
	{
		if (v == 0) // If the users doesnt want to make and initial deposit.
		{
			isa = false;
			intrest_Rate = 0.0085;
			account_Type = 2;
		}
		else // If the user does want to make an initial deposit.
		{
			isa = false;
			intrest_Rate = 0.0085;
			Transaction t("Initial Deposit", v);
			set_History(t);
			set_Balance(v);
			account_Type = 2;
		}
	}
}
// Compute intrest function.
double Savings::compute_Intrest(int t)	// Will take an amount of years and see how much the balance will increase.
{
	double temp = (get_Balance() * pow((1 + intrest_Rate / 12), 12 * t));
	return temp;
}
//Deposit functon.
void Savings::deposit(double v)	// Deposits into the account.
{
	Transaction t("Deposit", v);		// Creates a new transaction.
	set_Balance(get_Balance() + v);		// Adds to the balance.
	set_History(t);						// Pushes the transaction to the history.
	cout << ">>> Success!!!" << endl;	// Tells the user its worked.
}
//Withdrawal function.
void Savings::withdraw(double v)	// Allows the user to remove from the accounts balance.
{
	if (get_Balance() == 0)		// If balance is empty.
	{
		cout << ">>> Account is empty!" << endl;
	}
	else if (get_Balance() >= v)	// If the Account has sufficient funds.
	{
		Transaction t("Withdrawal", v);		// Creates a new transaction object.
		set_Balance(get_Balance() - v);		// Removes from the balance.
		set_History(t);						// Pushes the transaction to the history.
		cout << ">>> Success!!!" << endl;	// tells the user it wokred.
	}
	else if (get_Balance() < v)		// If the withdrawal amount is bigger then the balance.
	{
		// Informs the user they cant remove that amount of cash.
		cout << ">>> Withdrawal ammount is too large!" << endl;
		cout << ">>> Current balance is: " << char(156) << get_Balance() << endl;
	}
}
//Code for to_String method.
void Savings::to_String()	// Displays all information in a nice way to the user.
{
	if (isa == true)	// If the isa bit is true 
	{
		cout << ">>> ISA Savings Account" << endl;
	}
	else if (isa == false)	// If the isa bit is false.
	{
		cout << ">>> Savings Account" << endl;
	}
	cout << ">>> Current balance is: " << char(156) << get_Balance() << "\n" << endl;
	for (int i = get_History().size(); i > 0; i--)
	{
		get_History()[i - 1].to_String();
	}
	/*
		Example: Savings
		Savings Account
		>>> Current balance is: £8.45

		>>> Withdrawal: £46.55 at Sat Jan 16 15:43:24 2022
		>>> Deposit: £20.00 at Sat Jan 16 15:43:08 2022
		>>> Initial Deposit: £35.00 at Sat Jan 16 15:43:03 2022

		Example: ISA
		>>> ISA Savings Account
		>>> Current balance is: £1205

		>>> Withdrawal: £45.00 at Sat Jan 16 15:44:16 2022
		>>> Deposit: £250.00 at Sat Jan 16 15:44:09 2022
		>>> Initial Deposit: £1000.00 at Sat Jan 16 15:44:03 2022
	*/
}


//security
bool is_Number(string str)	// Checks if the given string is a number.
{
	return str.find_first_not_of("1234567890.") == string::npos;	// Identifies if the passed string contains any of the following characters.
}