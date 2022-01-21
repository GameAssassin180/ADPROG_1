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
void Transaction::set_Time_Stamp(){time_Stamp = time(0);}
void Transaction::set_Value(double v){value = v;}
//Getting.
string Transaction::get_Desc(){return desc;}
char* Transaction::get_Time_Stamp(){char* time = ctime(&time_Stamp);return time;}
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
	cout << ">>> " << get_Desc() << ": " << char(156) << fixed << setprecision(2) << get_Value() << " at " << get_Time_Stamp();
}


//Account class methods.
//Accessor methods.
//Setting.
void Account::set_Balance(double b){balance = b;}
void Account::set_History(Transaction t){history.push_back(t);}
//Getting.
double Account::get_Balance(){return balance;}
vector<Transaction> Account::get_History(){return history;}


//Current class methods.
//Accessor methods.
//Setting.
void Current::set_Overdraft(double o){overdraft = o;}
//Getting.
double Current::get_Overdraft(){return overdraft;}
//Code for to_String method.
void Current::to_String()
{
	cout << "\n>>> Current Account" << endl;
	cout << ">>> Current balance is: " << char(156) << get_Balance() << endl;
	cout << ">>> Current overdraft is: " << char(156) << overdraft << "\n" << endl;
	for (int i = get_History().size(); i > 0; i--)
	{			
		get_History()[i - 1].to_String();
	}
}
//Constructor for Current class.
Current::Current(double v)
{
	if (v == 0)
	{
		overdraft = 500;
		account_Type = 1;
	}
	else
	{
		Transaction t("Initial Deposit", v);
		overdraft = 500;
		set_History(t);
		set_Balance(v);
		account_Type = 1;
	}
}
//Deposit functon.
void Current::deposit(double v)
{
	if (get_Overdraft() == 500)
	{
		Transaction t("Deposit", v);
		set_History(t);
		set_Balance(get_Balance() + v);
		cout << ">>> Success!!!" << endl;
	}
	else if (overdraft == 0 and v <= 500 or overdraft < 500 and v < 500 - overdraft)
	{
		Transaction ot("Overdraft Deposit", v);
		overdraft = (overdraft + v);
		set_History(ot);
		cout << ">>> Success!!!" << endl;
	}
	else if (overdraft == 0 and v > 500)
	{
		double temp = v - 500;
		Transaction ot("Overdraft Deposit", 500);
		Transaction t("Deposit", temp);
		overdraft = 500;
		set_Balance(temp);
		set_History(ot);
		set_History(t);
		cout << ">>> Success!!!" << endl;
	}
	else if (overdraft < 500 and v > 500 - overdraft)
	{
		double temp = v - (500 - overdraft);
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
	if (overdraft == 0 and get_Balance() == 0)
	{
		cout << ">>> Overdraft empty cannot withdraw." << endl;
	}
	else if (get_Balance() == 0 and overdraft < v)
	{
		cout << ">>> Withdrawal too big not enough in overdraft" << endl;
		cout << ">>> Current overdraft is: " << char(156) << overdraft << endl;
	}
	else if (get_Balance() == 0 and overdraft >= v)
	{
		Transaction t("Overdraft Withdrawal", v);
		set_History(t);
		overdraft = (overdraft - v);
		cout << ">>> Success!!!" << endl;
	}
	else if (get_Balance() <= v and overdraft <= (v - get_Balance()))
	{
		cout << ">>> Withdrawal too big not enough in overdraft" << endl;
		cout << ">>> Current balance is: " << char(156) << get_Balance() << endl;
		cout << ">>> Current overdraft is: " << char(156) << overdraft << endl;
	}
	else if (get_Balance() <= v and overdraft >= (v - get_Balance()))
	{
		double temp = (v - get_Balance());
		Transaction t("Withdrawal", get_Balance());
		set_Balance(0);
		Transaction ot("Overdraft Withdrawal", temp);
		overdraft = (overdraft - temp);
		set_History(t);
		set_History(ot);
		cout << ">>> Success!!!" << endl;
	}
	else if (get_Balance() >= v)
	{
		Transaction t("Withdrawal", v);
		set_Balance(get_Balance() - v);
		set_History(t);
		cout << ">>> Success!!!" << endl;
	}
}

//Savings account methods.
//Constructor
//Savings
Savings::Savings(double v, bool b)
{
	if (b == true and v >= 1000)
	{
		isa = true;
		intrest_Rate = 0.0115;
		Transaction t("Initial Deposit", v);
		set_History(t);
		set_Balance(v);
		account_Type = 2;
	}
	else if (b == true and v < 1000)
	{
		cout << ">>> Account cannot be opened unless 1000 GBP is deposited" << endl;
	}
	else if (b == false)
	{
		if (v == 0)
		{
			isa = false;
			intrest_Rate = 0.0085;
			account_Type = 2;
		}
		else
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
double Savings::compute_Intrest(int t)
{
	double temp = (get_Balance() * pow((1 + intrest_Rate / 12), 12 * t));
	return temp;
}
void Savings::deposit(double v)
{
	Transaction t("Deposit", v);
	set_Balance(get_Balance() + v);
	set_History(t);
	cout << ">>> Success!!!" << endl;
}
void Savings::withdraw(double v)
{
	if (get_Balance() == 0)
	{
		cout << ">>> Account is empty!" << endl;
	}
	else if (get_Balance() >= v)
	{
		Transaction t("Withdrawal", v);
		set_Balance(get_Balance() - v);
		set_History(t);
		cout << ">>> Success!!!" << endl;
	}
	else if (get_Balance() < v)
	{
		cout << ">>> Withdrawal ammount is too large!" << endl;
		cout << ">>> Current balance is: " << char(156) << get_Balance() << endl;
	}
}
void Savings::to_String()
{
	if (isa == true)
	{
		cout << "\n>>> ISA Savings Account" << endl;
	}
	else if (isa == false)
	{
		cout << "\n>>> Savings Account" << endl;
	}
	cout << ">>> Current balance is: " << char(156) << get_Balance() << "\n" << endl;
	for (int i = get_History().size(); i > 0; i--)
	{
		get_History()[i - 1].to_String();
	}
}


//security
bool is_Number(string str)
{
	return str.find_first_not_of("1234567890.") == string::npos;
}